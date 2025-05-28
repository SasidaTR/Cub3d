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
