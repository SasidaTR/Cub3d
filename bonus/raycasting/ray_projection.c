/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:05 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	select_tex(t_ray *r, t_data *d)
{
	if (r->side == 1)
	{
		if (r->ray_y < 0)
			r->tex = d->map.tex_n;
		else
			r->tex = d->map.tex_s;
	}
	else
	{
		if (r->ray_x < 0)
			r->tex = d->map.tex_w;
		else
			r->tex = d->map.tex_e;
	}
	r->step = 1.0 * TEX_SIZE / r->line_height;
	r->tex_pos = (r->start - HEIGHT / 2 + r->line_height / 2) * r->step;
}
