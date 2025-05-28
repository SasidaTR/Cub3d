#include "../../include/cub3d.h"
#include <stdlib.h>

// Convert string values to RGB component
static int get_rgb_value(char **split, int index)
{
    int value = ft_atoi(split[index]);
    if (value < 0 || value > 255)
        return (-1);
    return (value);
}

// Parse comma-separated color string into integer
static int parse_color(char *line)
{
    char **split = ft_split(line, ',');
    int rgb[3];
    int status;

    if (!split)
        return (-1);
    if (split[0] && split[1] && split[2] && !split[3])
        status = 1;
    else
        status = -1;
    if (status == 1)
    {
        rgb[0] = get_rgb_value(split, 0);
        rgb[1] = get_rgb_value(split, 1);
        rgb[2] = get_rgb_value(split, 2);
        if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
            status = -1;
    }
    free_array(split);
    if (status == -1)
        return (-1);
    return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

// Assign parsed color to map floor or ceiling
static int assign_color_values(t_map *map, int color, char id)
{
    if (id == 'F')
    {
        map->floor[0] = (color >> 16) & 0xFF;
        map->floor[1] = (color >> 8) & 0xFF;
        map->floor[2] = color & 0xFF;
    }
    else if (id == 'C')
    {
        map->ceiling[0] = (color >> 16) & 0xFF;
        map->ceiling[1] = (color >> 8) & 0xFF;
        map->ceiling[2] = color & 0xFF;
    }
    else
        return (0);
    return (1);
}

// Public: parse floor or ceiling color line
int parse_colors(t_map *map, char *line, char id)
{
    char *clr = ft_strtrim(line + 1, " \t\n\r\f\v");
    int color;

    if (!clr)
        color = -1;
    else
        color = parse_color(clr);
    free(clr);
    if (color == -1)
        return (0);
    return (assign_color_values(map, color, id));
}
