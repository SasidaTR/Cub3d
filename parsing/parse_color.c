#include "../../include/cub3d.h"

int	parse_color(int color[3], char *line)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (free_array(rgb), 0);
	color[0] = ft_atoi(rgb[0]);
	color[1] = ft_atoi(rgb[1]);
	color[2] = ft_atoi(rgb[2]);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		return (free_array(rgb), 0);
	free_array(rgb);
	return (1);
}
