#include "../../include/cub3d.h"

// Called on key press: update key flags and process movement
int	handle_key(int keycode, t_data *data)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		close_window(data);
	else if (keycode == KEY_W)
		data->keys.w = 1;
	else if (keycode == KEY_S)
		data->keys.s = 1;
	else if (keycode == KEY_A)
		data->keys.a = 1;
	else if (keycode == KEY_D)
		data->keys.d = 1;
	else if (keycode == KEY_LEFT)
		data->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 1;

	process_movement(data);
	return (0);
}

// Called on key release: clear key flags
int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 0;
	else if (keycode == KEY_S)
		data->keys.s = 0;
	else if (keycode == KEY_A)
		data->keys.a = 0;
	else if (keycode == KEY_D)
		data->keys.d = 0;
	else if (keycode == KEY_LEFT)
		data->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 0;

	return (0);
}

// Update player position and rotation based on active keys
void	process_movement(t_data *data)
{
	double move_x;
	double move_y;

	move_x = 0.0;
	move_y = 0.0;
	handle_rotation(data);
	calc_move(data, &move_x, &move_y);
	apply_move(data, move_x, move_y);
}
