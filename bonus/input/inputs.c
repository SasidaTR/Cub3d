/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:56:56 by douzgane          #+#    #+#             */
/*   Updated: 2025/06/18 16:12:49 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	mouse_move(int x, int y, t_data *data)
{
	int	center_x;

	(void)y;
	center_x = WIDTH / 2;
	if (x != center_x)
	{
		rotate_cam(data, (x - center_x) * 0.002);
		mlx_mouse_move(data->mlx, data->win, center_x, HEIGHT / 2);
	}
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	if (keycode >= 0 && keycode < 300)
		data->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	data->keys[keycode] = 0;
	return (0);
}

int	close_window(t_data *data)
{
	free_all_resources(data);
	exit(0);
	return (0);
}
