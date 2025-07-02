/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:22:23 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:26:49 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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
	t_fov_params		p;
	t_line_draw_params	line_params;

	p = init_fov_params(data, tile_size);
	line_params.x0 = p.center_x;
	line_params.y0 = p.center_y;
	line_params.x1 = p.center_x + (int)(p.left_x * p.fov_len);
	line_params.y1 = p.center_y + (int)(p.left_y * p.fov_len);
	line_params.color = COLOR_FOV;
	draw_line(addr, line_params);
	line_params.x1 = p.center_x + (int)(p.right_x * p.fov_len);
	line_params.y1 = p.center_y + (int)(p.right_y * p.fov_len);
	draw_line(addr, line_params);
}

void	draw_player(t_data *data, char *addr, int tile_size)
{
	int					pos[2];
	int					center[2];
	int					end[2];
	t_tile_params		tile_params;
	t_line_draw_params	line_params;

	pos[0] = MINIMAP_MARGIN + (int)(data->map.player_x * tile_size) - 2;
	pos[1] = MINIMAP_MARGIN + (int)(data->map.player_y * tile_size) - 2;
	tile_params.x = pos[0];
	tile_params.y = pos[1];
	tile_params.size = 5;
	tile_params.color = COLOR_PLAYER;
	draw_tile(addr, tile_params);
	center[0] = pos[0] + 2;
	center[1] = pos[1] + 2;
	end[0] = center[0] + (int)(data->map.dir_x * tile_size * 0.7);
	end[1] = center[1] + (int)(data->map.dir_y * tile_size * 0.7);
	line_params.x0 = center[0];
	line_params.y0 = center[1];
	line_params.x1 = end[0];
	line_params.y1 = end[1];
	line_params.color = COLOR_PLAYER;
	draw_line(addr, line_params);
}
