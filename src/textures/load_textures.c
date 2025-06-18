/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:27 by douzgane          #+#    #+#             */
/*   Updated: 2025/06/18 15:58:28 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	load_textures(t_data *data)
{
	data->map.tex_n = mlx_xpm_file_to_image(data->mlx, data->map.N,
			&(int){TEX_SIZE}, &(int){TEX_SIZE});
	data->map.tex_s = mlx_xpm_file_to_image(data->mlx, data->map.S,
			&(int){TEX_SIZE}, &(int){TEX_SIZE});
	data->map.tex_w = mlx_xpm_file_to_image(data->mlx, data->map.W,
			&(int){TEX_SIZE}, &(int){TEX_SIZE});
	data->map.tex_e = mlx_xpm_file_to_image(data->mlx, data->map.E,
			&(int){TEX_SIZE}, &(int){TEX_SIZE});
	if (!data->map.tex_n || !data->map.tex_s || !data->map.tex_w
		|| !data->map.tex_e)
		return (0);
	return (1);
}
