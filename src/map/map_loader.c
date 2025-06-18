#include "../../include/cub3d.h"

void	display_map(t_data *d)
{
	void	*img;
	char	*addr;
	int		bpp;
	int		sl;
	int		endian;
	int		x;

	img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	addr = mlx_get_data_addr(img, &bpp, &sl, &endian);
	x = 0;
	while (x < WIDTH)
		render_column(d, addr, x++);
	mlx_put_image_to_window(d->mlx, d->win, img, 0, 0);
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
		return (close(fd), free_array(lines), print_error("invalid texture paths"));
	if (!read_map_lines(fd, &lines, &size))
		return (close(fd), free_array(lines),
			print_error("failed to read map lines"));
	close(fd);
	ok = validate_and_parse_map(map, lines);
	free_array(lines);
	return (ok);
}
