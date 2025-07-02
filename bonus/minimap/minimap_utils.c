/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:22:17 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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

void	draw_tile(char *addr, t_tile_params params)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < params.size)
	{
		dx = 0;
		while (dx < params.size)
		{
			put_pixel(addr, params.x + dx, params.y + dy, params.color);
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

static void	update_line_coords(t_line_params *p, int *err, int *x0, int *y0)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 > -p->dy)
	{
		*err -= p->dy;
		*x0 += p->sx;
	}
	if (e2 < p->dx)
	{
		*err += p->dx;
		*y0 += p->sy;
	}
}

void	draw_line(char *addr, t_line_draw_params params)
{
	t_line_params	p;
	int				err;
	int				x0;
	int				y0;

	x0 = params.x0;
	y0 = params.y0;
	p = init_line_params(x0, y0, params.x1, params.y1);
	err = p.dx - p.dy;
	while (1)
	{
		put_pixel(addr, x0, y0, params.color);
		if (x0 == params.x1 && y0 == params.y1)
			break ;
		update_line_coords(&p, &err, &x0, &y0);
	}
}
