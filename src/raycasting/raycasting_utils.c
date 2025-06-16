#include "../../include/cub3d.h"

int	get_tex_pixel(void *tex, int x, int y)
{
	int		bpp;
	int		line;
	int		endian;
	char	*adr;

	adr = mlx_get_data_addr(tex, &bpp, &line, &endian);
	if (!adr)
		return (0);
	return (*(int *)(adr + (y * line + x * (bpp / 8))));
}

void	draw_ceiling(t_data *d, char *addr, int x, int limit)
{
	int	y;
	int	color;

	color = (d->map.ceiling[0] << 16) | (d->map.ceiling[1] << 8) | d->map.ceiling[2];
	y = 0;
	while (y < limit)
	{
		*(int *)(addr + y * WIDTH * 4 + x * 4) = color;
		y++;
	}
}

void	draw_floor(t_data *d, char *addr, int x, int start)
{
	int	y;
	int	color;

	color = (d->map.floor[0] << 16) | (d->map.floor[1] << 8) | d->map.floor[2];
	y = start;
	while (y < HEIGHT)
	{
		*(int *)(addr + y * WIDTH * 4 + x * 4) = color;
		y++;
	}
}

void	draw_wall(t_ray *r, char *addr, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = r->start;
	while (y < r->end)
	{
		tex_y = (int)(r->tex_pos) & (TEX_SIZE - 1);
		r->tex_pos += r->step;
		color = get_tex_pixel(r->tex, r->tex_x, tex_y);
		if (r->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		*(int *)(addr + y * WIDTH * 4 + x * 4) = color;
		y++;
	}
}
