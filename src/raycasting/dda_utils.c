#include "../../include/cub3d.h"

// Advance ray to next grid line
void	advance_ray(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

// Check if ray position is within map bounds
int	is_valid_position(t_ray *ray, t_data *data)
{
	if (!data->map.map)
		return (0);
	if (ray->map_y < 0 || ft_array_size(data->map.map) <= ray->map_y)
		return (0);
	if (ray->map_x < 0 || ft_strlen(data->map.map[ray->map_y]) <= (size_t)ray->map_x)
		return (0);
	return (1);
}

// Check if ray hit a wall
int	check_wall_hit(t_ray *ray, t_data *data)
{
	if (!is_valid_position(ray, data))
		return (1);
	if (data->map.map[ray->map_y][ray->map_x] == '1')
	{
		ray->hit = 1;
		return (1);
	}
	return (0);
}
