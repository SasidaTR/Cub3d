#include "../../include/cub3d.h"

int	read_map_lines(int fd, char ***lines, int *size)
{
	char	*line;
	char	**tmp;

	while ((line = get_next_line(fd)))
	{
		tmp = ft_realloc(*lines, (*size) * sizeof(char *), (*size + 2) * sizeof(char *));
		if (!tmp)
			return (free(line), 0);
		*lines = tmp;
		(*lines)[(*size)++] = line;
		(*lines)[*size] = NULL;
	}
	return (1);
}

int	read_map_start(int fd, t_map *map, char ***lines, int *size)
{
	char	*line;

	while ((line = get_next_line(fd)))
	{
		if (assign_texture(&map->N, line, "NO")
			|| assign_texture(&map->S, line, "SO")
			|| assign_texture(&map->W, line, "WE")
			|| assign_texture(&map->E, line, "EA"))
			;
		else if (assign_color(map->floor, line, "F"))
			;
		else if (assign_color(map->ceiling, line, "C"))
			;
		else if (ft_strchr(line, '1'))
		{
			*lines = ft_calloc(2, sizeof(char *));
			if (!*lines)
				return (free(line), 0);
			(*lines)[0] = line;
			*size = 1;
			return (1);
		}
		free(line);
	}
	return (0);
}
