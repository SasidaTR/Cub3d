/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:27 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/16 20:25:05 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	cleanup_textures(t_data *data, int count)
{
	if (count >= 1 && data->map.tex_n)
		mlx_destroy_image(data->mlx, data->map.tex_n);
	if (count >= 2 && data->map.tex_s)
		mlx_destroy_image(data->mlx, data->map.tex_s);
	if (count >= 3 && data->map.tex_w)
		mlx_destroy_image(data->mlx, data->map.tex_w);
}

static int	load_single_texture(t_data *data, void **tex, char *path)
{
	int	w;
	int	h;

	*tex = mlx_xpm_file_to_image(data->mlx, path, &w, &h);
	if (!*tex || w != TEX_SIZE || h != TEX_SIZE)
		return (0);
	return (1);
}

int	load_textures(t_data *data)
{
	if (!load_single_texture(data, &data->map.tex_n, data->map.north))
		return (0);
	if (!load_single_texture(data, &data->map.tex_s, data->map.south))
		return (cleanup_textures(data, 1), 0);
	if (!load_single_texture(data, &data->map.tex_w, data->map.west))
		return (cleanup_textures(data, 2), 0);
	if (!load_single_texture(data, &data->map.tex_e, data->map.east))
		return (cleanup_textures(data, 3), 0);
	return (1);
}
