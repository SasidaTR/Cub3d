#include "../../include/cub3d.h"

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

static void	move_ws(t_data *d, double x, double y)
{
	double	new_x;
	double	new_y;

	if (d->keys[KEY_W])
	{
		new_x = x + d->map.dir_x * MOVE_SPEED;
		new_y = y + d->map.dir_y * MOVE_SPEED;
		if (d->map.map[(int)y][(int)new_x] != '1')
			d->map.player_x = new_x;
		if (d->map.map[(int)new_y][(int)x] != '1')
			d->map.player_y = new_y;
	}
	if (d->keys[KEY_S])
	{
		new_x = x - d->map.dir_x * MOVE_SPEED;
		new_y = y - d->map.dir_y * MOVE_SPEED;
		if (d->map.map[(int)y][(int)new_x] != '1')
			d->map.player_x = new_x;
		if (d->map.map[(int)new_y][(int)x] != '1')
			d->map.player_y = new_y;
	}
}

static void	move_ad(t_data *d, double x, double y)
{
	double	new_x;
	double	new_y;

	if (d->keys[KEY_A])
	{
		new_x = x - d->map.plane_x * MOVE_SPEED;
		new_y = y - d->map.plane_y * MOVE_SPEED;
		if (d->map.map[(int)y][(int)new_x] != '1')
			d->map.player_x = new_x;
		if (d->map.map[(int)new_y][(int)x] != '1')
			d->map.player_y = new_y;
	}
	if (d->keys[KEY_D])
	{
		new_x = x + d->map.plane_x * MOVE_SPEED;
		new_y = y + d->map.plane_y * MOVE_SPEED;
		if (d->map.map[(int)y][(int)new_x] != '1')
			d->map.player_x = new_x;
		if (d->map.map[(int)new_y][(int)x] != '1')
			d->map.player_y = new_y;
	}
}

static void	rotate_cam(t_data *d, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = d->map.dir_x;
	d->map.dir_x = d->map.dir_x * cos(rot) - d->map.dir_y * sin(rot);
	d->map.dir_y = old_dir_x * sin(rot) + d->map.dir_y * cos(rot);
	old_plane_x = d->map.plane_x;
	d->map.plane_x = d->map.plane_x * cos(rot) - d->map.plane_y * sin(rot);
	d->map.plane_y = old_plane_x * sin(rot) + d->map.plane_y * cos(rot);
}

void	update_player(t_data *data)
{
	double	cur_x;
	double	cur_y;

	cur_x = data->map.player_x;
	cur_y = data->map.player_y;
	move_ws(data, cur_x, cur_y);
	move_ad(data, cur_x, cur_y);
	if (data->keys[KEY_LEFT])
		rotate_cam(data, -ROT_SPEED);
	if (data->keys[KEY_RIGHT])
		rotate_cam(data, ROT_SPEED);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}
