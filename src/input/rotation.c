#include "../../include/cub3d.h"

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->map.dir_x;
	data->map.dir_x = data->map.dir_x * cos(ROT_SPEED)
		- data->map.dir_y * sin(ROT_SPEED);
	data->map.dir_y = old_dir_x * sin(ROT_SPEED)
		+ data->map.dir_y * cos(ROT_SPEED);
	old_plane_x = data->map.plane_x;
	data->map.plane_x = data->map.plane_x * cos(ROT_SPEED)
		- data->map.plane_y * sin(ROT_SPEED);
	data->map.plane_y = old_plane_x * sin(ROT_SPEED)
		+ data->map.plane_y * cos(ROT_SPEED);
	display_map(data);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->map.dir_x;
	data->map.dir_x = data->map.dir_x * cos(-ROT_SPEED)
		- data->map.dir_y * sin(-ROT_SPEED);
	data->map.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ data->map.dir_y * cos(-ROT_SPEED);
	old_plane_x = data->map.plane_x;
	data->map.plane_x = data->map.plane_x * cos(-ROT_SPEED)
		- data->map.plane_y * sin(-ROT_SPEED);
	data->map.plane_y = old_plane_x * sin(-ROT_SPEED)
		+ data->map.plane_y * cos(-ROT_SPEED);
	display_map(data);
}
