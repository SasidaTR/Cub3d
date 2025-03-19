#include "../include/cub3d.h"

int	parse_color(int color[3], char *line)
{
	char	**rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (0);
	color[0] = ft_atoi(rgb[0]);
	color[1] = ft_atoi(rgb[1]);
	color[2] = ft_atoi(rgb[2]);
	free_array(rgb);
	return (1);
}

void	init_player(t_map *map, int y, int x, char dir)
{
	map->player_x = x + 0.5;
	map->player_y = y + 0.5;
	map->dir_x = (dir == 'E') - (dir == 'W');
	map->dir_y = (dir == 'S') - (dir == 'N');
	map->plane_x = (dir == 'N' || dir == 'S') ? 0.66 * ((dir == 'N') - (dir == 'S')) : 0;
	map->plane_y = (dir == 'E' || dir == 'W') ? 0.66 * ((dir == 'E') - (dir == 'W')) : 0;
}

int	parse_map_data(t_map *map, char **lines, int i)
{
	int	y = 0;
	int	x;

	map->map = ft_calloc(ft_array_size(lines + i) + 1, sizeof(char *));
	while (lines[i])
	{
		map->map[y] = ft_strdup(lines[i]);
		x = 0;
		while (map->map[y][x])
		{
			if (ft_strchr("NSWE", map->map[y][x]))
				init_player(map, y, x, map->map[y][x]);
			x++;
		}
		y++;
		i++;
	}
	return (1);
}

int	load_map(char *path, t_map *map)
{
	int		fd = open(path, O_RDONLY);
	char	*line;

	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		if (!ft_strncmp(line, "N ", 2))
			map->N = ft_strtrim(line + 2, " \n");
		else if (!ft_strncmp(line, "S ", 2))
			map->S = ft_strtrim(line + 2, " \n");
		else if (!ft_strncmp(line, "W ", 2))
			map->W = ft_strtrim(line + 2, " \n");
		else if (!ft_strncmp(line, "E ", 2))
			map->E = ft_strtrim(line + 2, " \n");
		else if (!ft_strncmp(line, "F ", 2))
			parse_color(map->floor, line + 2);
		else if (!ft_strncmp(line, "C ", 2))
			parse_color(map->ceiling, line + 2);
		else if (ft_isdigit(line[0]) || ft_strchr(line, '1'))
			break ;
		free(line);
	}
	char	**map_lines = ft_calloc(100, sizeof(char *));
	int		j = 0;
	while (line)
	{
		map_lines[j++] = line;
		line = get_next_line(fd);
	}
	close(fd);
	return (parse_map_data(map, map_lines, 0));
}
