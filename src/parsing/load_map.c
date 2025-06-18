#include "../../include/cub3d.h"

static int	assign_color(int color[3], char *line, char *id)
{
	int		len;
	char	*trimmed;

	len = ft_strlen(id);
	if (!ft_strncmp(line, id, len) && line[len] == ' ')
	{
		trimmed = ft_strtrim(line + len + 1, " \n");
		if (!parse_color(color, trimmed))
			return (free(trimmed), 0);
		free(trimmed);
		return (1);
	}
	return (0);
}

static int	assign_texture(char **dst, char *line, char *id)
{
	int		len;

	len = ft_strlen(id);
	if (!ft_strncmp(line, id, len) && line[len] == ' ')
	{
		*dst = ft_strtrim(line + len + 1, " \n");
		return (1);
	}
	return (0);
}

static int	read_map_start(int fd, t_map *map, char ***lines, int *size)
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

static int	read_map_lines(int fd, char ***lines, int *size)
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

int	validate_and_parse_map(t_map *map, char **lines)
{
	if (!validate_required_elements(map))
		return (print_error("missing required elements"), 0);
	if (!validate_map_empty_lines(lines))
		return (print_error("map contains invalid empty lines"), 0);
	if (!validate_map_chars(lines))
		return (print_error("map contains invalid characters"), 0);
	if (!is_map_closed(lines))
		return (print_error("map is not closed"), 0);
	if (!parse_map_data(map, lines, 0))
		return (print_error("failed to parse map"), 0);
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
	ok = validate_and_parse_map(map, lines);
	free_array(lines);
	return (ok);
}
