#include "../../include/cub3d.h"

void	calculate_minimap_params(t_data *data, int rows, int cols)
{
	int	max_w;
	int	max_h;
	int	scale;
	int	w;
	int	h;
	int	x0;
	int	y0;

	max_w = WIDTH / 5;
	max_h = HEIGHT / 5;
	scale = max_w / cols < max_h / rows ? max_w / cols : max_h / rows;
	if (scale < 1)
		scale = 1;
	w = cols * scale;
	h = rows * scale;
	x0 = 10;
	y0 = 10;
	if (x0 + w > WIDTH)
		x0 = WIDTH - w - 1;
	if (y0 + h > HEIGHT)
		y0 = HEIGHT - h - 1;
	data->map.minimap_scale = scale;
	data->map.minimap_w = w;
	data->map.minimap_h = h;
	data->map.minimap_x = x0;
	data->map.minimap_y = y0;
}
