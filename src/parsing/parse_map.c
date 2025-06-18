#include "../../include/cub3d.h"

void	init_player(t_map *map, int y, int x, char dir)
{
	map->player_x = x + 0.5;
	map->player_y = y + 0.5;
	map->dir_x = (dir == 'E') - (dir == 'W');
	map->dir_y = (dir == 'S') - (dir == 'N');
	map->plane_x = (dir == 'N') * 0.66 - (dir == 'S') * 0.66;
	map->plane_y = (dir == 'E') * 0.66 - (dir == 'W') * 0.66;
}

static int	check_player_spawn(t_map *map, int y, int x, int *found)
{
	if (ft_strchr("NSWE", map->map[y][x]))
	{
		if (*found)
			return (0);
		init_player(map, y, x, map->map[y][x]);
		*found = 1;
	}
	return (1);
}

char	**copy_map_lines(char **lines, int start)
{
	int		size;
	int		i;
	char	**copy;

	size = ft_array_size(lines + start);
	copy = ft_calloc(size + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(lines[start + i]);
		if (!copy[i])
			return (free_array(copy), NULL);
		i++;
	}
	return (copy);
}

int	parse_map_data(t_map *map, char **lines, int i)
{
	int	y;
	int	x;
	int	found;

	found = 0;
	map->map = copy_map_lines(lines, i);
	if (!map->map)
		return (0);
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (!check_player_spawn(map, y, x, &found))
				return (0);
			x++;
		}
		y++;
	}
	return (found);
}
