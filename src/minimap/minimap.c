#include "../../include/cub3d.h"

void	draw_minimap(t_data *data)
{
	char	**map;
	int		rows;
	int		cols;

	map = data->map.map;
	rows = 0;
	cols = 0;
	while (map[rows])
		rows++;
	if (rows == 0)
		return ;
	while (map[0][cols])
		cols++;
	if (cols == 0)
		return ;
	calculate_minimap_params(data, rows, cols);
	draw_minimap_walls(data, map, rows, cols);
	draw_minimap_fov(data);
	draw_minimap_player(data);
}
