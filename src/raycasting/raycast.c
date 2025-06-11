#include "../../include/cub3d.h"

static void	init_ray(t_ray *r, t_data *d, int x)
{
	r->cam = 2.0 * x / WIDTH - 1;
	r->ray_x = d->map.dir_x + d->map.plane_x * r->cam;
	r->ray_y = d->map.dir_y + d->map.plane_y * r->cam;
	r->map_x = (int)d->map.player_x;
	r->map_y = (int)d->map.player_y;
	r->delta_x = fabs(1.0 / r->ray_x);
	r->delta_y = fabs(1.0 / r->ray_y);
	r->step_x = (r->ray_x < 0) ? -1 : 1;
	r->step_y = (r->ray_y < 0) ? -1 : 1;
	if (r->ray_x < 0)
		r->side_x = (d->map.player_x - r->map_x) * r->delta_x;
	else
		r->side_x = (r->map_x + 1.0 - d->map.player_x) * r->delta_x;
	if (r->ray_y < 0)
		r->side_y = (d->map.player_y - r->map_y) * r->delta_y;
	else
		r->side_y = (r->map_y + 1.0 - d->map.player_y) * r->delta_y;
}

static void	run_dda(t_ray *r, char **map)
{
	while (map[r->map_y][r->map_x] != '1')
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
}

static void	project_wall(t_ray *r, t_data *d)
{
	if (r->side == 0)
		r->dist = r->side_x - r->delta_x;
	else
		r->dist = r->side_y - r->delta_y;
	r->line_height = (int)(HEIGHT / r->dist);
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
	if ((r->side == 0 && r->ray_x > 0) || (r->side == 1 && r->ray_y < 0))
		r->tex_x = TEX_SIZE - r->tex_x - 1;
}

static void	select_tex(t_ray *r, t_data *d)
{
	if (r->side == 1)
		r->tex = (r->ray_y < 0) ? d->map.tex_n : d->map.tex_s;
	else
		r->tex = (r->ray_x < 0) ? d->map.tex_w : d->map.tex_e;
	r->step = 1.0 * TEX_SIZE / r->line_height;
	r->tex_pos = (r->start - HEIGHT / 2 + r->line_height / 2) * r->step;
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
	draw_floor(d, addr, x, r.end);
}
