#include "../../include/cub3d.h"

int	load_textures(t_data *data)
{
	data->map.tex_n = mlx_xpm_file_to_image(data->mlx, data->map.N, &(int){64}, &(int){64});
	data->map.tex_s = mlx_xpm_file_to_image(data->mlx, data->map.S, &(int){64}, &(int){64});
	data->map.tex_w = mlx_xpm_file_to_image(data->mlx, data->map.W, &(int){64}, &(int){64});
	data->map.tex_e = mlx_xpm_file_to_image(data->mlx, data->map.E, &(int){64}, &(int){64});
	if (!data->map.tex_n || !data->map.tex_s || !data->map.tex_w || !data->map.tex_e)
		return (0);
	return (1);
}
