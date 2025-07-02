/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:05 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	init_ray_delta(t_ray *r)
{
	if (r->ray_x == 0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->ray_x);
	if (r->ray_y == 0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->ray_y);
	if (r->ray_x < 0)
		r->step_x = -1;
	else
		r->step_x = 1;
	if (r->ray_y < 0)
		r->step_y = -1;
	else
		r->step_y = 1;
}

static void	init_ray_side(t_ray *r, t_data *d)
{
	if (r->ray_x < 0)
		r->side_x = (d->map.player_x - r->map_x) * r->delta_x;
	else
		r->side_x = (r->map_x + 1.0 - d->map.player_x) * r->delta_x;
	if (r->ray_y < 0)
		r->side_y = (d->map.player_y - r->map_y) * r->delta_y;
	else
		r->side_y = (r->map_y + 1.0 - d->map.player_y) * r->delta_y;
}

static void	init_ray(t_ray *r, t_data *d, int x)
{
	r->cam = 2.0 * (x - (WIDTH / 2)) / 800;
	r->ray_x = d->map.dir_x + d->map.plane_x * r->cam;
	r->ray_y = d->map.dir_y + d->map.plane_y * r->cam;
	r->map_x = (int)d->map.player_x;
	r->map_y = (int)d->map.player_y;
	init_ray_delta(r);
	init_ray_side(r, d);
}

void	render_column(t_data *d, char *addr, int x)
{
	t_ray	r;

	init_ray(&r, d, x);
	run_dda(&r, d->map.map);
	project_wall(&r, d);
	select_tex(&r, d);
	draw_ceiling(d, addr, x, r.start);
	draw_wall(&r, addr, x);
	draw_floor(d, addr, x, r.end + 1);
}
