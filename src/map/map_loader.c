/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:57:25 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/16 19:02:06 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	render_frame(t_data *d, void *img, char *addr)
{
	int	x;

	x = 0;
	while (x < WIDTH)
		render_column(d, addr, x++);
	mlx_put_image_to_window(d->mlx, d->win, img, 0, 0);
}

void	display_map(t_data *d)
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;

	img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_len, &(int){0});
	render_frame(d, img, addr);
	mlx_destroy_image(d->mlx, img);
}

int	validate_and_parse_map(t_map *map, char **lines)
{
	if (!validate_required_elements(map))
		return (print_error("missing texture or color definitions "
				"(NO, SO, WE, EA, F, C)"), 0);
	if (!validate_map_empty_lines(lines))
		return (print_error("map contains invalid empty lines "
				"within the grid"), 0);
	if (!validate_map_chars(lines))
		return (print_error("map contains invalid characters "
				"(only 0,1,N,S,E,W allowed)"), 0);
	if (!is_map_closed(lines))
		return (print_error("map is not properly closed by walls (1)"), 0);
	if (!parse_map_data(map, lines, 0))
		return (print_error("map parsing failed - "
				"no player spawn point found"), 0);
	return (1);
}

int	process_map_file(int fd, t_map *map, char ***lines, int *size)
{
	if (!read_map_start(fd, map, lines, size))
		return (get_next_line_cleanup(fd),
			print_error("invalid map format - missing NO/SO/WE/EA "
				"textures or F/C colors"), 0);
	if (!validate_textures(map))
		return (get_next_line_cleanup(fd), free_array(*lines),
			print_error("texture files not found - "
				"check .xpm file paths"), 0);
	if (!read_map_lines(fd, lines, size))
		return (get_next_line_cleanup(fd), free_array(*lines),
			print_error("cannot read map data - "
				"file may be corrupted"), 0);
	return (1);
}

int	load_map(char *path, t_map *map)
{
	int		fd;
	char	**lines;
	int		size;
	int		ok;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_error("cannot open map file - "
				"check file path and permissions"));
	lines = NULL;
	size = 0;
	if (!process_map_file(fd, map, &lines, &size))
		return (close(fd), 0);
	get_next_line_cleanup(fd);
	close(fd);
	ok = validate_and_parse_map(map, lines);
	free_array(lines);
	return (ok);
}
