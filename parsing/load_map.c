#include "../../include/cub3d.h"

static int	read_map_start(int fd, t_map *map, char ***lines, int *size)
{
	char	*line;
	char	*trimmed;

	while ((line = get_next_line(fd)))
	{
		if (!ft_strncmp(line, "NO ", 3))
			map->N = ft_strtrim(line + 3, " \n");
		else if (!ft_strncmp(line, "SO ", 3))
			map->S = ft_strtrim(line + 3, " \n");
		else if (!ft_strncmp(line, "WE ", 3))
			map->W = ft_strtrim(line + 3, " \n");
		else if (!ft_strncmp(line, "EA ", 3))
			map->E = ft_strtrim(line + 3, " \n");
		else if (!ft_strncmp(line, "F ", 2))
		{
			trimmed = ft_strtrim(line + 2, " \n");
			if (!parse_color(map->floor, trimmed))
				return (free(trimmed), free(line), 0);
			free(trimmed);
		}
		else if (!ft_strncmp(line, "C ", 2))
		{
			trimmed = ft_strtrim(line + 2, " \n");
			if (!parse_color(map->ceiling, trimmed))
				return (free(trimmed), free(line), 0);
			free(trimmed);
		}
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

static int	read_map_lines(int fd, char ***lines, int *size)
{
	char	*line;
	char	**tmp;

	while ((line = get_next_line(fd)))
	{
		tmp = ft_realloc(*lines, (*size) * sizeof(char *), (*size + 2)
				* sizeof(char *));
		if (!tmp)
			return (free(line), 0);
		*lines = tmp;
		(*lines)[(*size)++] = line;
		(*lines)[*size] = NULL;
	}
	return (1);
}

int	load_map(char *path, t_map *map)
{
	int		fd;
	char	**lines;
	int		size;
	int		ok;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_error("failed to open map file"));
	lines = NULL;
	size = 0;
	if (!read_map_start(fd, map, &lines, &size))
		return (close(fd), print_error("invalid map elements"));
	if (!validate_textures(map))
		return (close(fd), free_array(lines), print_error("invalid texture paths"));
	if (!read_map_lines(fd, &lines, &size))
		return (close(fd), free_array(lines),
			print_error("failed to read map lines"));
	close(fd);
	if (!validate_map_empty_lines(lines))
		return (free_array(lines), print_error("map contains invalid empty lines"));
	if (!validate_map_chars(lines))
		return (free_array(lines), print_error("map contains invalid characters"));
	if (!is_map_closed(lines))
		return (free_array(lines), print_error("map is not closed"));
	ok = parse_map_data(map, lines, 0);
	if (!ok)
		print_error("failed to parse map");
	free_array(lines);
	return (ok);
}
