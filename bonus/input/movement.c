/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:56:56 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	try_move(t_data *d, double new_x, double new_y)
{
	if (!check_wall_collision(d, new_x, new_y))
	{
		d->map.player_x = new_x;
		d->map.player_y = new_y;
		return ;
	}
	if (!check_wall_collision(d, new_x, d->map.player_y))
	{
		d->map.player_x = new_x;
	}
	if (!check_wall_collision(d, d->map.player_x, new_y))
	{
		d->map.player_y = new_y;
	}
}

static void	add_movement(double *x, double *y, double dx, double dy)
{
	*x += dx * MOVE_SPEED;
	*y += dy * MOVE_SPEED;
}

static void	move_player(t_data *d)
{
	double	x;
	double	y;
	double	move_x;
	double	move_y;

	x = d->map.player_x;
	y = d->map.player_y;
	move_x = 0;
	move_y = 0;
	if (d->keys[KEY_W])
		add_movement(&move_x, &move_y, d->map.dir_x, d->map.dir_y);
	if (d->keys[KEY_S])
		add_movement(&move_x, &move_y, -d->map.dir_x, -d->map.dir_y);
	if (d->keys[KEY_A])
		add_movement(&move_x, &move_y, -d->map.plane_x, -d->map.plane_y);
	if (d->keys[KEY_D])
		add_movement(&move_x, &move_y, d->map.plane_x, d->map.plane_y);
	try_move(d, x + move_x, y + move_y);
}

void	rotate_cam(t_data *d, double rot)
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
	move_player(data);
	if (data->keys[KEY_LEFT])
		rotate_cam(data, -ROT_SPEED);
	if (data->keys[KEY_RIGHT])
		rotate_cam(data, ROT_SPEED);
}
