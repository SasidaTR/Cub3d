#include "../../include/cub3d.h"

int	is_map_closed(char **map)
{
	int	y;
	int	x;

	if (!map || !map[0])
		return (0);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (y == 0 || !map[y + 1] || x == 0 || !map[y][x + 1] ||
					map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
					map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

