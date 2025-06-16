#include "../../include/cub3d.h"

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
	map->dir_x = (dir == 'E') - (dir == 'W');
	map->dir_y = (dir == 'S') - (dir == 'N');
	map->plane_x = (dir == 'N') * 0.66 - (dir == 'S') * 0.66;
	map->plane_y = (dir == 'E') * 0.66 - (dir == 'W') * 0.66;
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

/*
#include "../../include/cub3d.h"

int	check_wall_collision(t_data *data, double new_x, double new_y)
{
	int	map_x;
	int	map_y;
	int	map_height;

	if (!data || !data->map.map)
		return (1);
		
	map_height = 0;
	while (data->map.map[map_height])
		map_height++;
		
	map_x = (int)new_x;
	map_y = (int)new_y;
	
	if (map_x < 0 || map_y < 0 || map_y >= map_height)
		return (1);
		
	if (!data->map.map[map_y] || map_x >= (int)ft_strlen(data->map.map[map_y]))
		return (1);
		
	if (data->map.map[map_y][map_x] == '1')
		return (1);
		
	return (0);
}
*/