#include "../../include/cub3d.h"

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307
#define MOVE_SPEED 0.005
#define ROT_SPEED 0.005

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	data->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	data->keys[keycode] = 0;
	return (0);
}

void	update_player(t_data *data)
{
	double	new_x;
	double	new_y;
	double	old_dir_x;
	double	old_plane_x;
	double	cur_x = data->map.player_x;
	double	cur_y = data->map.player_y;

	if (data->keys[KEY_W])
	{
		new_x = cur_x + data->map.dir_x * MOVE_SPEED;
		new_y = cur_y + data->map.dir_y * MOVE_SPEED;
		if (data->map.map[(int)cur_y][(int)new_x] != '1')
			data->map.player_x = new_x;
		if (data->map.map[(int)new_y][(int)cur_x] != '1')
			data->map.player_y = new_y;
	}
	if (data->keys[KEY_S])
	{
		new_x = cur_x - data->map.dir_x * MOVE_SPEED;
		new_y = cur_y - data->map.dir_y * MOVE_SPEED;
		if (data->map.map[(int)cur_y][(int)new_x] != '1')
			data->map.player_x = new_x;
		if (data->map.map[(int)new_y][(int)cur_x] != '1')
			data->map.player_y = new_y;
	}
	if (data->keys[KEY_A])
	{
		new_x = cur_x - data->map.plane_x * MOVE_SPEED;
		new_y = cur_y - data->map.plane_y * MOVE_SPEED;
		if (data->map.map[(int)cur_y][(int)new_x] != '1')
			data->map.player_x = new_x;
		if (data->map.map[(int)new_y][(int)cur_x] != '1')
			data->map.player_y = new_y;
	}
	if (data->keys[KEY_D])
	{
		new_x = cur_x + data->map.plane_x * MOVE_SPEED;
		new_y = cur_y + data->map.plane_y * MOVE_SPEED;
		if (data->map.map[(int)cur_y][(int)new_x] != '1')
			data->map.player_x = new_x;
		if (data->map.map[(int)new_y][(int)cur_x] != '1')
			data->map.player_y = new_y;
	}
	if (data->keys[KEY_LEFT])
	{
		old_dir_x = data->map.dir_x;
		data->map.dir_x = data->map.dir_x * cos(-ROT_SPEED) - data->map.dir_y * sin(-ROT_SPEED);
		data->map.dir_y = old_dir_x * sin(-ROT_SPEED) + data->map.dir_y * cos(-ROT_SPEED);
		old_plane_x = data->map.plane_x;
		data->map.plane_x = data->map.plane_x * cos(-ROT_SPEED) - data->map.plane_y * sin(-ROT_SPEED);
		data->map.plane_y = old_plane_x * sin(-ROT_SPEED) + data->map.plane_y * cos(-ROT_SPEED);
	}
	if (data->keys[KEY_RIGHT])
	{
		old_dir_x = data->map.dir_x;
		data->map.dir_x = data->map.dir_x * cos(ROT_SPEED) - data->map.dir_y * sin(ROT_SPEED);
		data->map.dir_y = old_dir_x * sin(ROT_SPEED) + data->map.dir_y * cos(ROT_SPEED);
		old_plane_x = data->map.plane_x;
		data->map.plane_x = data->map.plane_x * cos(ROT_SPEED) - data->map.plane_y * sin(ROT_SPEED);
		data->map.plane_y = old_plane_x * sin(ROT_SPEED) + data->map.plane_y * cos(ROT_SPEED);
	}
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}
