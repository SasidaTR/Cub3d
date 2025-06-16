#include "../../include/cub3d.h"

static int	get_map_height(t_data *data)
{
	int	height;

	height = 0;
	while (data->map.map[height])
		height++;
	return (height);
}

static int	is_out_of_bounds(int x, int y, int height, int width)
{
	if (x < 0 || y < 0 || y >= height || x >= width)
		return (1);
	return (0);
}

static int	is_wall(t_data *data, int x, int y)
{
	if (data->map.map[y][x] == '1')
		return (1);
	return (0);
}

static int	is_point_valid(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;
	int	map_height;
	int	map_width;

	map_height = get_map_height(data);
	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= map_height)
		return (0);
	if (!data->map.map[map_y])
		return (0);
	map_width = ft_strlen(data->map.map[map_y]);
	if (is_out_of_bounds(map_x, map_y, map_height, map_width))
		return (0);
	if (is_wall(data, map_x, map_y))
		return (0);
	return (1);
}

int	check_wall_collision(t_data *data, double new_x, double new_y)
{
	double	buffer;

	if (!data || !data->map.map)
		return (1);
	buffer = 0.1;
	if (!is_point_valid(data, new_x, new_y))
		return (1);
	if (!is_point_valid(data, new_x + buffer, new_y))
		return (1);
	if (!is_point_valid(data, new_x - buffer, new_y))
		return (1);
	if (!is_point_valid(data, new_x, new_y + buffer))
		return (1);
	if (!is_point_valid(data, new_x, new_y - buffer))
		return (1);
	return (0);
}
