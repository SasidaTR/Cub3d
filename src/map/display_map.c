#include "../include/cub3d.h"

int	get_tex_pixel(void *tex, int x, int y)
{
	int	bpp, line, end;
	char *adr = mlx_get_data_addr(tex, &bpp, &line, &end);
	return (*(int *)(adr + (y * line + x * (bpp / 8))));
}

void	display_map(t_data *data)
{
	int	x, y, tex_x, tex_y;
	double cam_x, ray_x, ray_y, delta_x, delta_y, dist;
	double side_x, side_y, step, tex_pos, wall_x;
	int	map_x, map_y, step_x, step_y, side, lh, ds, de;
	void *img = mlx_new_image(data->mlx, 800, 600);
	char *addr = mlx_get_data_addr(img, &(int){32}, &(int){3200}, &(int){0});

	for (x = 0; x < 800; x++)
	{
		cam_x = 2 * x / 800.0 - 1;
		ray_x = data->map.dir_x + data->map.plane_x * cam_x;
		ray_y = data->map.dir_y + data->map.plane_y * cam_x;
		map_x = data->map.player_x;
		map_y = data->map.player_y;
		delta_x = fabs(1 / ray_x);
		delta_y = fabs(1 / ray_y);
		step_x = ray_x < 0 ? -1 : 1;
		step_y = ray_y < 0 ? -1 : 1;
		side_x = ray_x < 0 ? (data->map.player_x - map_x) * delta_x : (map_x + 1.0 - data->map.player_x) * delta_x;
		side_y = ray_y < 0 ? (data->map.player_y - map_y) * delta_y : (map_y + 1.0 - data->map.player_y) * delta_y;
		while (data->map.map[map_y][map_x] != '1')
		{
			if (side_x < side_y && !(side = 0))
				side_x += delta_x, map_x += step_x;
			else
				side_y += delta_y, map_y += step_y, side = 1;
		}
		dist = side ? (side_y - delta_y) : (side_x - delta_x);
		lh = (int)(600 / dist);
		ds = -lh / 2 + 300;
		de = lh / 2 + 300;
		wall_x = side ? data->map.player_x + dist * ray_x : data->map.player_y + dist * ray_y;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * 64);
		if ((side == 0 && ray_x > 0) || (side == 1 && ray_y < 0))
			tex_x = 63 - tex_x;
		step = 64.0 / lh;
		tex_pos = (ds - 300 + lh / 2) * step;
		void *tex = side ? (ray_y < 0 ? data->map.tex_n : data->map.tex_s)
						 : (ray_x < 0 ? data->map.tex_w : data->map.tex_e);
		y = ds < 0 ? 0 : ds;
		de = de >= 600 ? 599 : de;
		while (y < de)
		{
			tex_y = (int)tex_pos & 63;
			tex_pos += step;
			*(int *)(addr + (y * 3200 + x * 4)) = get_tex_pixel(tex, tex_x, tex_y);
			y++;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}
