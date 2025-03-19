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

int	get_texture_pixel(void *img, int x, int y)
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*addr;

	addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	return (*(int *)(addr + (y * size_line + x * (bpp / 8))));
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
			{
				if (x < data->map.player_x)
					color = get_texture_pixel(data->map.tex_w, x % 64, y % 64);
				else if (x > data->map.player_x)
					color = get_texture_pixel(data->map.tex_e, x % 64, y % 64);
				else if (y < data->map.player_y)
					color = get_texture_pixel(data->map.tex_n, x % 64, y % 64);
				else
					color = get_texture_pixel(data->map.tex_s, x % 64, y % 64);
			}
			draw_square(addr, size_line, bpp, x * TILE_SIZE + offset_x, y * TILE_SIZE + offset_y, color);
			x++;
		}
		y++;
	}
}

void	display_map(t_data *data)
{
	int		x;
	int		y;
	int		hit;
	int		map_x;
	int		map_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		tex_x;
	int		tex_y;
	double	wall_x;
	double	step;
	double	tex_pos;
	void	*tex_img;

	img = mlx_new_image(data->mlx, 800, 600);
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	x = 0;
	while (x < 800)
	{
		camera_x = 2 * x / 800.0 - 1;
		ray_dir_x = data->map.dir_x + data->map.plane_x * camera_x;
		ray_dir_y = data->map.dir_y + data->map.plane_y * camera_x;
		map_x = (int)data->map.player_x;
		map_y = (int)data->map.player_y;
		delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		hit = 0;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->map.player_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->map.player_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->map.player_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->map.player_y) * delta_dist_y;
		}
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (data->map.map[map_y][map_x] == '1')
				hit = 1;
		}
		perp_wall_dist = (side == 0) ? (map_x - data->map.player_x + (1 - step_x) / 2) / ray_dir_x
									 : (map_y - data->map.player_y + (1 - step_y) / 2) / ray_dir_y;
		line_height = (int)(600 / perp_wall_dist);
		draw_start = -line_height / 2 + 300;
		draw_end = line_height / 2 + 300;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= 600)
			draw_end = 599;
		wall_x = (side == 0) ? data->map.player_y + perp_wall_dist * ray_dir_y
							 : data->map.player_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * 64.0);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = 63 - tex_x;
		step = 64.0 / line_height;
		tex_pos = (draw_start - 300 + line_height / 2) * step;
		tex_img = side == 0 ? (ray_dir_x < 0 ? data->map.tex_w : data->map.tex_e)
							: (ray_dir_y < 0 ? data->map.tex_n : data->map.tex_s);
		y = draw_start;
		while (y < draw_end)
		{
			tex_y = (int)tex_pos & 63;
			tex_pos += step;
			*(int *)(addr + (y * size_line + x * (bpp / 8))) = get_texture_pixel(tex_img, tex_x, tex_y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}
