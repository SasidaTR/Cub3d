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
	{
		render_column(d, addr, x);
		x++;
	}
	mlx_put_image_to_window(d->mlx, d->win, img, 0, 0);
	mlx_destroy_image(d->mlx, img);
}

int	parse_color(int color[3], char *line)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (0);
	color[0] = ft_atoi(rgb[0]);
	color[1] = ft_atoi(rgb[1]);
	color[2] = ft_atoi(rgb[2]);
	free_array(rgb);
	return (1);
}

void	init_player(t_map *map, int y, int x, char dir)
{
	map->player_x = x + 0.5;
	map->player_y = y + 0.5;
	map->dir_x = 0;
	map->dir_y = 0;
	if (dir == 'N')
		map->dir_y = -1;
	else if (dir == 'S')
		map->dir_y = 1;
	else if (dir == 'E')
		map->dir_x = 1;
	else if (dir == 'W')
		map->dir_x = -1;
	map->plane_x = 0;
	map->plane_y = 0;
	if (dir == 'N')
		map->plane_x = 0.66;
	else if (dir == 'S')
		map->plane_x = -0.66;
	else if (dir == 'E')
		map->plane_y = 0.66;
	else if (dir == 'W')
		map->plane_y = -0.66;
}

int	parse_map_data(t_map *map, char **lines, int i)
{
	int	y;
	int	x;
	int	size;

	y = 0;
	size = ft_array_size(lines + i);
	map->map = ft_calloc(size + 1, sizeof(char *));
	if (!map->map)
		return (0);

	while (lines[i])
	{
		map->map[y] = ft_strdup(lines[i]);
		x = 0;
		while (map->map[y][x])
		{
			if (ft_strchr("NSWE", map->map[y][x]))
				init_player(map, y, x, map->map[y][x]);
			x++;
		}
		y++;
		i++;
	}
	return (1);
}

