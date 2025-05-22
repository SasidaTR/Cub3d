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
	{
		printf("Usage: ./cub3D <map.cub>\n");
		return (1);
	}
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 800, 600, "Cub3D");
	if (load_map(argv[1], &data.map) == 0)
	{
		printf("Error\nFailed to load map\n");
		return (1);
	}
	if (!load_textures(&data))
	{
		printf("Error\nFailed to load textures\n");
		return (1);
	}
	display_map(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
