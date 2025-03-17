#include "../../include/cub3d.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	printf("Key pressed : %d\n", keycode);

	if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}
