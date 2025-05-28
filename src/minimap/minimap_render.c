#include "../../include/cub3d.h"

static void	put_pixel(t_data *data, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	data->addr[y * (data->line_length / 4) + x] = color;
}

void	draw_minimap_border(t_data *data, int x0, int y0, int w, int h)
{
	int	x;
	int	y;
	int	x1;
	int	y1;

	x1 = x0 + w - 1;
	y1 = y0 + h - 1;
	y = y0;
	while (y <= y1)
	{
		put_pixel(data, x0, y, 0xCCCCCC);
		put_pixel(data, x1, y, 0xCCCCCC);
		y++;
	}
	x = x0;
	while (x <= x1)
	{
		put_pixel(data, x, y0, 0xCCCCCC);
		put_pixel(data, x, y1, 0xCCCCCC);
		x++;
	}
}

static void	draw_wall_block(t_data *data, int sx, int sy, int scale)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < scale)
	{
		dx = 0;
		while (dx < scale)
		{
			put_pixel(data, sx + dx, sy + dy, 0x8B4513);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap_walls(t_data *data, char **map, int rows, int cols)
{
	int	cy;
	int	cx;
	int	sx;
	int	sy;

	cy = 0;
	while (cy < rows)
	{
		cx = 0;
		while (cx < cols)
		{
			if (map[cy][cx] == '1')
			{
				sx = data->map.minimap_x + cx * data->map.minimap_scale;
				sy = data->map.minimap_y + cy * data->map.minimap_scale;
				draw_wall_block(data, sx, sy, data->map.minimap_scale);
			}
			cx++;
		}
		cy++;
	}
}
