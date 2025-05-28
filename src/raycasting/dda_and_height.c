#include "../../include/cub3d.h"
#include <math.h>

// Perform DDA algorithm until a wall is hit
void	perform_dda(t_ray *ray, t_data *data)
{
	int max_iterations = 1000; // Protection contre les boucles infinies
	int iterations = 0;
	
	if (isnan(ray->delta_dist_x) || isinf(ray->delta_dist_x))
	{
		ray->hit = 1;
		return;
	}
	if (isnan(ray->delta_dist_y) || isinf(ray->delta_dist_y))
	{
		ray->hit = 1;
		return;
	}
	while (ray->hit == 0 && iterations < max_iterations)
	{
		advance_ray(ray);
		
		if (check_wall_hit(ray, data))
			break;
		
		iterations++;
	}
	
	if (iterations >= max_iterations)
		ray->hit = 1;
}

// Compute perpendicular wall distance
static double compute_perp_wall_dist(t_ray *ray, t_data *data)
{
    double dist;
    double num;

    if (ray->side == 0 && ray->ray_dir_x != 0)
    {
        num = ray->map_x - data->map.player_x;
        num += (1.0 - ray->step_x) / 2.0;
        dist = num / ray->ray_dir_x;
    }
    else if (ray->side == 1 && ray->ray_dir_y != 0)
    {
        num = ray->map_y - data->map.player_y;
        num += (1.0 - ray->step_y) / 2.0;
        dist = num / ray->ray_dir_y;
    }
    else
        dist = 1.0;
    dist = fabs(dist);
    if (isnan(dist) || isinf(dist))
        dist = 1.0;
    if (dist < 0.001)
        dist = 0.001;
    if (dist > 1000.0)
        dist = 1000.0;
    return (dist);
}

// Compute line bounds based on perp wall distance
static void compute_line_bounds(t_ray *ray)
{
    int height_limit;

    height_limit = HEIGHT * 10;
    ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
    if (ray->line_height > height_limit)
        ray->line_height = height_limit;
    ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1;
}

void calculate_wall_height(t_ray *ray, t_data *data)
{
    ray->perp_wall_dist = compute_perp_wall_dist(ray, data);
    compute_line_bounds(ray);
}
