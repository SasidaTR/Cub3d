#include "../../include/cub3d.h"

// Handle rotation based on active keys
void	handle_rotation(t_data *data)
{
	if (data->keys.left)
		rotate_right(data);
	if (data->keys.right)
		rotate_left(data);
}

// Calculate movement delta based on active keys
void	calc_move(t_data *data, double *move_x, double *move_y)
{
	if (data->keys.w)
	{
		*move_x += data->map.dir_x * MOVE_SPEED;
		*move_y += data->map.dir_y * MOVE_SPEED;
	}
	if (data->keys.s)
	{
		*move_x -= data->map.dir_x * MOVE_SPEED;
		*move_y -= data->map.dir_y * MOVE_SPEED;
	}
	if (data->keys.a)
	{
		*move_x -= data->map.plane_x * MOVE_SPEED;
		*move_y -= data->map.plane_y * MOVE_SPEED;
	}
	if (data->keys.d)
	{
		*move_x += data->map.plane_x * MOVE_SPEED;
		*move_y += data->map.plane_y * MOVE_SPEED;
	}
}

// Apply movement if no collision detected
void	apply_move(t_data *data, double move_x, double move_y)
{
	double new_x;
	double new_y;

	if (move_x == 0.0 && move_y == 0.0)
		return;
	new_x = data->map.player_x + move_x;
	new_y = data->map.player_y + move_y;
	if (!check_wall_collision(data, new_x, new_y))
	{
		data->map.player_x = new_x;
		data->map.player_y = new_y;
		display_map(data);
	}
}
