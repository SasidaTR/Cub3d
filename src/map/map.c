#include "../../include/cub3d.h"

static void	create_image(t_data *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

static void	draw_image(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
}

static void	process_ray(t_data *data, int x)
{
	t_ray	ray;

	init_ray(&ray, data, x);
	calculate_ray(&ray, data);
	perform_dda(&ray, data);
	calculate_wall_height(&ray, data);
	draw_walls(data, &ray, x);
}

static void	cast_rays(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		process_ray(data, x);
		x++;
	}
}

void	display_map(t_data *data)
{
	create_image(data);
	cast_rays(data);
	draw_minimap(data);
	draw_image(data);
}
