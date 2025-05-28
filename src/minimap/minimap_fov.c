#include "../../include/cub3d.h"
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static void	put_pixel(t_data *data, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	data->addr[y * (data->line_length / 4) + x] = color;
}

static void	draw_fov_line(t_data *data, int px, int py, double angle, double length, int color)
{
	double	dx;
	double	dy;
	int		i;
	int		x;
	int		y;

	dx = cos(angle) * length;
	dy = sin(angle) * length;
	i = 0;
	while (i <= (int)length)
	{
		x = px + (int)(dx * i / length);
		y = py + (int)(dy * i / length);
		put_pixel(data, x, y, color);
		i++;
	}
}

void	draw_minimap_fov(t_data *data)
{
	int		px;
	int		py;
	double	angle;
	double	range;
	double	length;

	px = data->map.minimap_x + (int)(data->map.player_x * data->map.minimap_scale);
	py = data->map.minimap_y + (int)(data->map.player_y * data->map.minimap_scale);
	angle = atan2(data->map.dir_y, data->map.dir_x);
	range = 30 * M_PI / 180.0;
	length = data->map.minimap_scale * 2;
	draw_fov_line(data, px, py, angle - range, length, 0x00FF00);
	draw_fov_line(data, px, py, angle + range, length, 0x00FF00);
	draw_fov_line(data, px, py, angle, length, 0xFFFF00);
}
