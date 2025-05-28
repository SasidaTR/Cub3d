#include "../../include/cub3d.h"

// Main texture loading function that coordinates all texture operations
int	load_textures(t_data *data)
{
	int	width, height;

	if (!data->map.north || !data->map.south || !data->map.west || !data->map.east)
	{
		ft_putstr_fd("Error: Missing texture paths\n", 2);
		return (0);
	}

	data->map.tex_n = load_single_texture(data, data->map.north, &width, &height);
	data->map.tex_s = load_single_texture(data, data->map.south, &width, &height);
	data->map.tex_w = load_single_texture(data, data->map.west, &width, &height);
	data->map.tex_e = load_single_texture(data, data->map.east, &width, &height);
	
	if (!data->map.tex_n || !data->map.tex_s || !data->map.tex_w || !data->map.tex_e)
	{
		ft_putstr_fd("Error: Failed to load all wall textures\n", 2);
		return (0);
	}
	
	data->map.tex_width = width;
	data->map.tex_height = height;
	
	if (!load_texture_data(data))
		return (0);
	return (1);
}
