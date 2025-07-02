/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:27 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	load_textures(t_data *data)
{
	int	w;
	int	h;

	data->map.tex_n = mlx_xpm_file_to_image(data->mlx, data->map.north, &w, &h);
	if (!data->map.tex_n || w != TEX_SIZE || h != TEX_SIZE)
		return (0);
	data->map.tex_s = mlx_xpm_file_to_image(data->mlx, data->map.south, &w, &h);
	if (!data->map.tex_s || w != TEX_SIZE || h != TEX_SIZE)
		return (0);
	data->map.tex_w = mlx_xpm_file_to_image(data->mlx, data->map.west, &w, &h);
	if (!data->map.tex_w || w != TEX_SIZE || h != TEX_SIZE)
		return (0);
	data->map.tex_e = mlx_xpm_file_to_image(data->mlx, data->map.east, &w, &h);
	if (!data->map.tex_e || w != TEX_SIZE || h != TEX_SIZE)
		return (0);
	return (1);
}
