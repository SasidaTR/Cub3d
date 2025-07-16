/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:15:00 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/16 19:02:06 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_printf("Error: MLX initialization failed\n"
				"Please check if X11 display is available\n"), 0);
	return (1);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, main_loop, data);
}
