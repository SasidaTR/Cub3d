#include "../include/cub3d.h"

int	main_loop(t_data *data)
{
	update_player(data);
	display_map(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Usage: ./cub3D <map.cub>\n"), 1);
	ft_bzero(&data, sizeof(t_data));
	if (!load_map(argv[1], &data.map))
		return (1);
	// protection a fonds !
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		free_map_resources(&data.map, NULL);
		return (printf("Error\nFailed to initialize MLX\n"), 1);
	}
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data.win)
	{
		free_map_resources(&data.map, data.mlx);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (printf("Error\nFailed to create window\n"), 1);
	}
	if (!load_textures(&data))
	{
		free_all_resources(&data);
		return (printf("Error\nFailed to load textures\n"), 1);
	}
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
	free_all_resources(&data);
	return (0);
}
