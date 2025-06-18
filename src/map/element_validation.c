#include "../../include/cub3d.h"

static int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_textures(t_map *map)
{
	if (!map->N || !map->S || !map->W || !map->E)
		return (0);
	if (!file_exists(map->N) || !file_exists(map->S) || !file_exists(map->W)
		|| !file_exists(map->E))
		return (0);
	return (1);
}

int	validate_required_elements(t_map *map)
{
	if (!map->N || !map->S || !map->W || !map->E)
		return (0);
	if (map->floor[0] == -1 || map->floor[1] == -1 || map->floor[2] == -1)
		return (0);
	if (map->ceiling[0] == -1 || map->ceiling[1] == -1 || map->ceiling[2] == -1)
		return (0);
	return (1);
}
