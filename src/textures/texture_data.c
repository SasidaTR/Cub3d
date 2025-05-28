#include "../../include/cub3d.h"

// Load texture data addresses for all wall textures
static int	get_texture_addresses(t_data *data, 
		int *bpp_n, int *line_n, int *endian_n,
		int *bpp_s, int *line_s, int *endian_s,
		int *bpp_w, int *line_w, int *endian_w,
		int *bpp_e, int *line_e, int *endian_e)
{
	data->map.tex_data_n = (char *)mlx_get_data_addr(data->map.tex_n,
			bpp_n, line_n, endian_n);
	
	data->map.tex_data_s = (char *)mlx_get_data_addr(data->map.tex_s,
			bpp_s, line_s, endian_s);
	
	data->map.tex_data_w = (char *)mlx_get_data_addr(data->map.tex_w,
			bpp_w, line_w, endian_w);
		
	data->map.tex_data_e = (char *)mlx_get_data_addr(data->map.tex_e,
			bpp_e, line_e, endian_e);
	
	if (!data->map.tex_data_n || !data->map.tex_data_s || 
		!data->map.tex_data_w || !data->map.tex_data_e)
	{
		ft_putstr_fd("Error: Failed to get wall texture data\n", 2);
		return (0);
	}
	return (1);
}

// Store texture parameters for each wall texture
static void	store_texture_parameters(t_data *data,
		int bpp_n, int line_n, int endian_n,
		int bpp_s, int line_s, int endian_s,
		int bpp_w, int line_w, int endian_w,
		int bpp_e, int line_e, int endian_e)
{
	data->map.tex_n_bpp = bpp_n;
	data->map.tex_n_line_length = line_n;
	data->map.tex_n_endian = endian_n;
	data->map.tex_s_bpp = bpp_s;
	data->map.tex_s_line_length = line_s;
	data->map.tex_s_endian = endian_s;
	data->map.tex_w_bpp = bpp_w;
	data->map.tex_w_line_length = line_w;
	data->map.tex_w_endian = endian_w;
	data->map.tex_e_bpp = bpp_e;
	data->map.tex_e_line_length = line_e;
	data->map.tex_e_endian = endian_e;
}

// Validate and set texture dimensions
static void	validate_texture_dimensions(t_data *data)
{
	if (data->map.tex_width <= 0)
		data->map.tex_width = TEX_SIZE;
	if (data->map.tex_height <= 0)
		data->map.tex_height = TEX_SIZE;
}

int	load_texture_data(t_data *data)
{
	int	bpp_n, line_n, endian_n;
	int	bpp_s, line_s, endian_s;
	int	bpp_w, line_w, endian_w;
	int	bpp_e, line_e, endian_e;

	if (!data->map.tex_n || !data->map.tex_s || !data->map.tex_w || !data->map.tex_e)
	{
		ft_putstr_fd("Error: Texture data not initialized\n", 2);
		return (0);
	}

	if (!get_texture_addresses(data, &bpp_n, &line_n, &endian_n,
			&bpp_s, &line_s, &endian_s, &bpp_w, &line_w, &endian_w,
			&bpp_e, &line_e, &endian_e))
		return (0);
	
	store_texture_parameters(data, bpp_n, line_n, endian_n,
		bpp_s, line_s, endian_s, bpp_w, line_w, endian_w,
		bpp_e, line_e, endian_e);
	
	validate_texture_dimensions(data);
	
	return (1);
}
