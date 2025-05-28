#include "../../include/cub3d.h"
#include <math.h>

// Initialize ray parameters for given screen column
void init_ray(t_ray *ray, t_data *data, int x)
{
    ray->camera_x = 2 * x / (double)WIDTH - 1;
    ray->ray_dir_x = data->map.dir_x + data->map.plane_x * ray->camera_x;
    ray->ray_dir_y = data->map.dir_y + data->map.plane_y * ray->camera_x;
    ray->map_x = (int)data->map.player_x;
    ray->map_y = (int)data->map.player_y;
    
    if (fabs(ray->ray_dir_x) < 1e-10)
        ray->delta_dist_x = 1e10;
    else
        ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
        
    if (fabs(ray->ray_dir_y) < 1e-10)
        ray->delta_dist_y = 1e10;
    else
        ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
    
    if (isnan(ray->delta_dist_x) || isinf(ray->delta_dist_x))
        ray->delta_dist_x = 1e10;
    if (isnan(ray->delta_dist_y) || isinf(ray->delta_dist_y))
        ray->delta_dist_y = 1e10;
        
    ray->hit = 0;
}

// Determine initial step and side distances for DDA
void calculate_ray(t_ray *ray, t_data *data)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (data->map.player_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - data->map.player_x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (data->map.player_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - data->map.player_y) * ray->delta_dist_y;
    }
}
