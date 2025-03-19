#include "../include/cub3d.h"

int	get_tex_pixel(void *tex, int x, int y)
{
	int	bpp, line, end;
	char *adr = mlx_get_data_addr(tex, &bpp, &line, &end);
	return (*(int *)(adr + (y * line + x * (bpp / 8))));
}

void	display_map(t_data *data)
{
	int		x, y;
	void	*img;
	char	*addr;
	int		bpp, sl, endian;

	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	addr = mlx_get_data_addr(img, &bpp, &sl, &endian);
	for (x = 0; x < WIDTH; x++)
	{
		double cam_x = 2 * x / (double)WIDTH - 1;
		double ray_x = data->map.dir_x + data->map.plane_x * cam_x;
		double ray_y = data->map.dir_y + data->map.plane_y * cam_x;
		int map_x = (int)data->map.player_x;
		int map_y = (int)data->map.player_y;
		double delta_x = fabs(1 / ray_x);
		double delta_y = fabs(1 / ray_y);
		int step_x = ray_x < 0 ? -1 : 1;
		int step_y = ray_y < 0 ? -1 : 1;
		double side_x = ray_x < 0 ? (data->map.player_x - map_x) * delta_x : (map_x + 1.0 - data->map.player_x) * delta_x;
		double side_y = ray_y < 0 ? (data->map.player_y - map_y) * delta_y : (map_y + 1.0 - data->map.player_y) * delta_y;
		int side;
		while (data->map.map[map_y][map_x] != '1')
		{
			if (side_x < side_y)
				side_x += delta_x, map_x += step_x, side = 0;
			else
				side_y += delta_y, map_y += step_y, side = 1;
		}
		double dist = side ? (side_y - delta_y) : (side_x - delta_x);
		int line_height = (int)(HEIGHT / dist);
		int draw_start = -line_height / 2 + HEIGHT / 2;
		int draw_end = line_height / 2 + HEIGHT / 2;
		draw_start = draw_start < 0 ? 0 : draw_start;
		draw_end = draw_end >= HEIGHT ? HEIGHT - 1 : draw_end;

		double wall_x = side ? data->map.player_x + dist * ray_x : data->map.player_y + dist * ray_y;
		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * TEX_SIZE);
		if ((side == 0 && ray_x > 0) || (side == 1 && ray_y < 0))
			tex_x = TEX_SIZE - tex_x - 1;

		double step = 1.0 * TEX_SIZE / line_height;
		double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
		void *tex = side ? (ray_y < 0 ? data->map.tex_n : data->map.tex_s)
						 : (ray_x < 0 ? data->map.tex_w : data->map.tex_e);
		for (y = 0; y < draw_start; y++)
			*(int *)(addr + y * sl + x * (bpp / 8)) = (data->map.ceiling[0] << 16 | data->map.ceiling[1] << 8 | data->map.ceiling[2]);
		for (y = draw_end; y < HEIGHT; y++)
			*(int *)(addr + y * sl + x * (bpp / 8)) = (data->map.floor[0] << 16 | data->map.floor[1] << 8 | data->map.floor[2]);

		for (y = draw_start; y < draw_end; y++)
		{
			int tex_y = (int)tex_pos & (TEX_SIZE - 1);
			tex_pos += step;
			int color = get_tex_pixel(tex, tex_x, tex_y);
			*(int *)(addr + y * sl + x * (bpp / 8)) = color;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}
