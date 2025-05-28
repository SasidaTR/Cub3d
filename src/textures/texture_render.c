#include "../../include/cub3d.h"

// Get texture data for East/West walls (vertical sides)
static void	get_vertical_wall_texture(t_ray *ray, t_data *data,
		char **texture_data, int *line_length, int *bits_per_pixel)
{
	if (ray->ray_dir_x > 0)
	{
		*texture_data = data->map.tex_data_e;  // East wall
		*line_length = data->map.tex_e_line_length;
		*bits_per_pixel = data->map.tex_e_bpp;
	}
	else
	{
		*texture_data = data->map.tex_data_w;  // West wall
		*line_length = data->map.tex_w_line_length;
		*bits_per_pixel = data->map.tex_w_bpp;
	}
}

// Get texture data for North/South walls (horizontal sides)
static void	get_horizontal_wall_texture(t_ray *ray, t_data *data,
		char **texture_data, int *line_length, int *bits_per_pixel)
{
	if (ray->ray_dir_y > 0)
	{
		*texture_data = data->map.tex_data_s;  // South wall
		*line_length = data->map.tex_s_line_length;
		*bits_per_pixel = data->map.tex_s_bpp;
	}
	else
	{
		*texture_data = data->map.tex_data_n;  // North wall
		*line_length = data->map.tex_n_line_length;
		*bits_per_pixel = data->map.tex_n_bpp;
	}
}

// Get texture data and parameters based on wall direction
static void	get_wall_texture_data(t_ray *ray, t_data *data, 
		char **texture_data, int *line_length, int *bits_per_pixel)
{
	if (ray->side == 0)
		get_vertical_wall_texture(ray, data, texture_data, line_length, bits_per_pixel);
	else
		get_horizontal_wall_texture(ray, data, texture_data, line_length, bits_per_pixel);
}

// Validate texture coordinates and ensure they're within bounds
static void	validate_texture_coordinates(t_ray *ray, t_data *data, int *tex_y)
{
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	if (ray->tex_x >= data->map.tex_width)
		ray->tex_x = data->map.tex_width - 1;

	*tex_y = (int)ray->tex_pos & (data->map.tex_height - 1);
	ray->tex_pos += ray->step;

	if (*tex_y < 0)
		*tex_y = 0;
	if (*tex_y >= data->map.tex_height)
		*tex_y = data->map.tex_height - 1;
}

// Get pixel color from texture based on direction
int	get_texture_color(t_ray *ray, t_data *data)
{
	int		tex_y;
	char	*texture_data;
	int		*pixel;
	int		offset;
	int		line_length;
	int		bits_per_pixel;

	validate_texture_coordinates(ray, data, &tex_y);
	get_wall_texture_data(ray, data, &texture_data, &line_length, &bits_per_pixel);

	if (!texture_data)
		return (0xFF00FF);

	offset = tex_y * line_length + ray->tex_x * (bits_per_pixel / 8);
	
	if (offset < 0 || offset >= (data->map.tex_height * line_length))
		return (0xFF00FF);
	
	pixel = (int *)(texture_data + offset);
	
	return (*pixel);
}
