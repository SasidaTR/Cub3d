/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:05 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	update_ray_position(t_ray *r)
{
	if (r->side_x < r->side_y)
	{
		r->side_x += r->delta_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_y += r->delta_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

static int	check_hit(t_ray *r, char **map)
{
	int	map_height;
	int	map_width;

	map_height = 0;
	while (map[map_height])
		map_height++;
	if (r->map_y < 0 || r->map_y >= map_height)
		return (1);
	map_width = ft_strlen(map[r->map_y]);
	if (r->map_x < 0 || r->map_x >= map_width)
		return (1);
	if (map[r->map_y][r->map_x] == '1')
		return (1);
	return (0);
}

void	run_dda(t_ray *r, char **map)
{
	while (!check_hit(r, map))
		update_ray_position(r);
}

void	project_wall(t_ray *r, t_data *d)
{
	if (r->side == 0)
		r->dist = r->side_x - r->delta_x;
	else
		r->dist = r->side_y - r->delta_y;
	r->line_height = (int)(600 / r->dist);
	r->start = HEIGHT / 2 - r->line_height / 2;
	if (r->start < 0)
		r->start = 0;
	r->end = HEIGHT / 2 + r->line_height / 2;
	if (r->end >= HEIGHT)
		r->end = HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = d->map.player_y + r->dist * r->ray_y;
	else
		r->wall_x = d->map.player_x + r->dist * r->ray_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * TEX_SIZE);
	if ((r->side == 0 && r->ray_x < 0) || (r->side == 1 && r->ray_y > 0))
		r->tex_x = TEX_SIZE - r->tex_x - 1;
}
