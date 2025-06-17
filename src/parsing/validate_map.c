#include "../../include/cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	validate_map_empty_lines(char **map)
{
	int	y;
	int	map_started;
	int	j;

	y = 0;
	map_started = 0;
	while (map[y])
	{
		if (!is_empty_line(map[y]))
			map_started = 1;
		else if (map_started)
		{
			j = y + 1;
			while (map[j])
			{
				if (!is_empty_line(map[j]))
					return (0);
				j++;
			}
		}
		y++;
	}
	return (1);
}

int	validate_map_chars(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr("01NSEW \n", map[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	is_map_closed(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (y == 0 || !map[y + 1] || x == 0 || !map[y][x + 1] || map[y
					- 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x
					- 1] == ' ' || map[y][x + 1] == ' ')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

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
