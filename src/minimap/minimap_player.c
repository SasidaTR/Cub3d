#include "../../include/cub3d.h"

t_fov_params	init_fov_params(t_data *data, int tile_size)
{
	t_fov_params	p;
	double			len_left;
	double			len_right;

	p.center_x = MINIMAP_MARGIN + (int)(data->map.player_x * tile_size);
	p.center_y = MINIMAP_MARGIN + (int)(data->map.player_y * tile_size);
	p.fov_len = tile_size * 2;
	p.left_x = data->map.dir_x - data->map.plane_x;
	p.left_y = data->map.dir_y - data->map.plane_y;
	p.right_x = data->map.dir_x + data->map.plane_x;
	p.right_y = data->map.dir_y + data->map.plane_y;
	len_left = sqrt(p.left_x * p.left_x + p.left_y * p.left_y);
	len_right = sqrt(p.right_x * p.right_x + p.right_y * p.right_y);
	p.left_x /= len_left;
	p.left_y /= len_left;
	p.right_x /= len_right;
	p.right_y /= len_right;
	return (p);
}

void	draw_fov(t_data *data, char *addr, int tile_size)
{
	t_fov_params	p;

	p = init_fov_params(data, tile_size);
	draw_line(addr, p.center_x, p.center_y, p.center_x + (int)(p.left_x
			* p.fov_len), p.center_y + (int)(p.left_y * p.fov_len), COLOR_FOV);
	draw_line(addr, p.center_x, p.center_y, p.center_x + (int)(p.right_x
			* p.fov_len), p.center_y + (int)(p.right_y * p.fov_len), COLOR_FOV);
}

void	draw_player(t_data *data, char *addr, int tile_size)
{
	int	pos[2];
	int	center[2];
	int	end[2];

	pos[0] = MINIMAP_MARGIN + (int)(data->map.player_x * tile_size) - 2;
	pos[1] = MINIMAP_MARGIN + (int)(data->map.player_y * tile_size) - 2;
	draw_tile(addr, pos[0], pos[1], 5, COLOR_PLAYER);
	center[0] = pos[0] + 2;
	center[1] = pos[1] + 2;
	end[0] = center[0] + (int)(data->map.dir_x * tile_size * 0.7);
	end[1] = center[1] + (int)(data->map.dir_y * tile_size * 0.7);
	draw_line(addr, center[0], center[1], end[0], end[1], COLOR_PLAYER);
}
