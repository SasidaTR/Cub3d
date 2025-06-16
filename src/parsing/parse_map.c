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

int	parse_map_data(t_map *map, char **lines, int i)
{
	int	y;
	int	x;
	int	size;
	int	player_found;

	y = 0;
	player_found = 0;
	size = ft_array_size(lines + i);
	map->map = ft_calloc(size + 1, sizeof(char *));
	if (!map->map)
		return (0);
	while (lines[i])
	{
		map->map[y] = ft_strdup(lines[i]);
		x = 0;
		while (map->map[y][x])
		{
			if (ft_strchr("NSWE", map->map[y][x]))
			{
				if (player_found)
					return (0);
				init_player(map, y, x, map->map[y][x]);
				player_found = 1;
			}
			x++;
		}
		y++;
		i++;
	}
	return (player_found);
}
