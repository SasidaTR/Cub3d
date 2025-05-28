#include "../include/cub3d.h"

// Initialize MLX and window
static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
}

// Initialize key states
static void	init_keys(t_data *data)
{
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->keys.left = 0;
	data->keys.right = 0;
}

// Initialize all data structures
void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(*data));
	init_mlx(data);
	init_keys(data);
}

// Load map and textures
int	load_resources(t_data *data, char *map_file)
{
	if (!load_map(map_file, &data->map))
	{
		ft_putstr_fd("Error: Failed to load map. Check format and content.\n", 2);
		return (1);
	}
	if (!load_textures(data))
	{
		ft_putstr_fd("Error: Failed to load textures. Check file paths.\n", 2);
		return (1);
	}
	return (0);
}
