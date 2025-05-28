#include "../../include/cub3d.h"

// Calculate wall texture coordinates based on ray hit
void	calculate_wall_texture(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->wall_x = data->map.player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = data->map.player_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);

	ray->tex_x = (int)(ray->wall_x * (double)data->map.tex_width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = data->map.tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = data->map.tex_width - ray->tex_x - 1;

	ray->step = 1.0 * data->map.tex_height / ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * ray->step;
}
