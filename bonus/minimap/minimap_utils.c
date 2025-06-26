#include "../../include/cub3d.h"

static void	put_pixel(char *addr, int x, int y, int color)
{
	int	offset;
	int	bg_color;
	int	blended_color;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = y * WIDTH * 4 + x * 4;
	bg_color = *(int *)(addr + offset);
	blended_color = ((int)(((bg_color >> 16) & 0xFF) * (1.0 - MINIMAP_ALPHA)
				+ ((color >> 16) & 0xFF) * MINIMAP_ALPHA)) << 16;
	blended_color |= ((int)(((bg_color >> 8) & 0xFF) * (1.0 - MINIMAP_ALPHA)
				+ ((color >> 8) & 0xFF) * MINIMAP_ALPHA)) << 8;
	blended_color |= (int)((bg_color & 0xFF) * (1.0 - MINIMAP_ALPHA)
			+ (color & 0xFF) * MINIMAP_ALPHA);
	*(int *)(addr + offset) = blended_color;
}

void	draw_tile(char *addr, int x, int y, int size, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < size)
	{
		dx = 0;
		while (dx < size)
		{
			put_pixel(addr, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

t_line_params	init_line_params(int x0, int y0, int x1, int y1)
{
	t_line_params	params;

	params.dx = abs(x1 - x0);
	params.dy = abs(y1 - y0);
	if (x0 < x1)
		params.sx = 1;
	else
		params.sx = -1;
	if (y0 < y1)
		params.sy = 1;
	else
		params.sy = -1;
	return (params);
}

void	draw_line(char *addr, int x0, int y0, int x1, int y1, int color)
{
	t_line_params	p;
	int				err;
	int				e2;

	p = init_line_params(x0, y0, x1, y1);
	err = p.dx - p.dy;
	while (1)
	{
		put_pixel(addr, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -p.dy)
		{
			err -= p.dy;
			x0 += p.sx;
		}
		if (e2 < p.dx)
		{
			err += p.dx;
			y0 += p.sy;
		}
	}
}
