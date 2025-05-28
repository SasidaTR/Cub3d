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

static void	draw_player_circle(t_data *data, int px, int py, int r)
{
	int	dx;
	int	dy;

	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
				put_pixel(data, px + dx, py + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap_player(t_data *data)
{
	int	scale;
	int	x0;
	int	y0;
	int	px;
	int	py;
	int	r;

	scale = data->map.minimap_scale;
	x0 = data->map.minimap_x;
	y0 = data->map.minimap_y;
	px = x0 + (int)(data->map.player_x * scale);
	py = y0 + (int)(data->map.player_y * scale);
	r = scale / 2;
	if (r < 2)
		r = 2;
	draw_player_circle(data, px, py, r);
}
