#include "../../include/cub3d.h"

#define TILE_SIZE 20

void	draw_square(char *addr, int size_line, int bpp, int x, int y, int color)
{
	int	i;
	int	j;
	int	pixel;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			pixel = ((y + i) * size_line + (x + j) * (bpp / 8));
			*(int *)(addr + pixel) = color;
			j++;
		}
		i++;
	}
}

void	fill_background(char *addr, int size_line, int bpp, int *color)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			pixel = (y * size_line + x * (bpp / 8));
			*(int *)(addr + pixel) = (y < 300)
				? (color[0] << 16 | color[1] << 8 | color[2])
				: (color[3] << 16 | color[4] << 8 | color[5]);
			x++;
		}
		y++;
	}
}

void	draw_map(t_data *data, char *addr, int size_line, int bpp)
{
	int	x;
	int	y;
	int	color;
	int	offset_x;
	int	offset_y;

	offset_x = 400 - (data->map.player_x * TILE_SIZE);
	offset_y = 300 - (data->map.player_y * TILE_SIZE);
	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			color = 0x000000;
			if (data->map.map[y][x] == '1')
				color = 0xFFFFFF;
			draw_square(addr, size_line, bpp, x * TILE_SIZE + offset_x, y * TILE_SIZE + offset_y, color);
			x++;
		}
		y++;
	}
}

void	display_map(t_data *data)
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		color[6];

	color[0] = data->map.ceiling[0];
	color[1] = data->map.ceiling[1];
	color[2] = data->map.ceiling[2];
	color[3] = data->map.floor[0];
	color[4] = data->map.floor[1];
	color[5] = data->map.floor[2];
	img = mlx_new_image(data->mlx, 800, 600);
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	fill_background(addr, size_line, bpp, color);
	draw_map(data, addr, size_line, bpp);
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}
