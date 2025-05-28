#include "../../include/cub3d.h"

// Validate texture file exists and is readable
int	validate_texture_file(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Cannot open texture file: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	close(fd);
	return (1);
}

// Load individual texture and validate size
void	*load_single_texture(t_data *data, char *path, int *w, int *h)
{
	void	*texture;

	if (!validate_texture_file(path))
		return (NULL);
	
	texture = mlx_xpm_file_to_image(data->mlx, path, w, h);
	if (!texture)
	{
		ft_putstr_fd("Error: Failed to load texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
	
	if (*w != TEX_SIZE || *h != TEX_SIZE)
	{
		ft_putstr_fd("Warning: Texture size mismatch in ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" (expected 64x64)\n", 2);
	}
	
	return (texture);
}
