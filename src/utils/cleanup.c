#include "../../include/cub3d.h"

static void	cleanup_textures(t_data *data)
{
	if (data->map.tex_n)
		mlx_destroy_image(data->mlx, data->map.tex_n);
	if (data->map.tex_s)
		mlx_destroy_image(data->mlx, data->map.tex_s);
	if (data->map.tex_w)
		mlx_destroy_image(data->mlx, data->map.tex_w);
	if (data->map.tex_e)
		mlx_destroy_image(data->mlx, data->map.tex_e);
	if (data->map.tex_floor)
		mlx_destroy_image(data->mlx, data->map.tex_floor);
	if (data->map.tex_ceiling)
		mlx_destroy_image(data->mlx, data->map.tex_ceiling);
}

static void	cleanup_map_data(t_data *data)
{
	if (data->map.map)
		free_array(data->map.map);
	if (data->map.north)
		free(data->map.north);
	if (data->map.south)
		free(data->map.south);
	if (data->map.west)
		free(data->map.west);
	if (data->map.east)
		free(data->map.east);
}

int	close_window(t_data *data)
{
	cleanup_textures(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	cleanup_map_data(data);
	exit(0);
	return (0);
}
