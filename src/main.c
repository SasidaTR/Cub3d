#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	int		result;
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Usage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	init_data(&data);
	result = load_resources(&data, argv[1]);
	if (result != 0)
		return (result);
	display_map(&data);
	setup_event_hooks(&data);
	mlx_loop(data.mlx);
	return (0);
}

// Setup MLX event hooks
void	setup_event_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, handle_key, data);
	mlx_hook(data->win, 3, 1L << 1, handle_key_release, data);
	mlx_hook(data->win, 17, 0, close_window, data);
}
