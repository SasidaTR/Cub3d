/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:57:25 by douzgane          #+#    #+#             */
/*   Updated: 2025/06/25 10:34:45 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	render_frame(t_data *d, void *img, char *addr)
{
	int	x;

	x = 0;
	while (x < WIDTH)
		render_column(d, addr, x++);
	draw_minimap(d, addr);  // Ajouter la minimap par-dessus le rendu 3D
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
		return (print_error("missing required elements"), 0);
	if (!validate_map_empty_lines(lines))
		return (print_error("map contains invalid empty lines"), 0);
	if (!validate_map_chars(lines))
		return (print_error("map contains invalid characters"), 0);
	if (!is_map_closed(lines))
		return (print_error("map is not closed"), 0);
	if (!parse_map_data(map, lines, 0))
		return (print_error("failed to parse map"), 0);
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
		return (print_error("failed to open map file"));
	lines = NULL;
	size = 0;
	if (!read_map_start(fd, map, &lines, &size))
		return (close(fd), print_error("invalid map elements"));
	if (!validate_textures(map))
		return (close(fd), free_array(lines),
			print_error("invalid texture paths"));
	if (!read_map_lines(fd, &lines, &size))
		return (close(fd), free_array(lines),
			print_error("failed to read map lines"));
	close(fd);
	ok = validate_and_parse_map(map, lines);
	free_array(lines);
	return (ok);
}
