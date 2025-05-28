#include "../../include/cub3d.h"
#include <stdlib.h>

// Check if a line belongs to the map (all chars '0','1',' ','N','S','E','W')
static int is_line_empty_for_map(const char *line)
{
    if (!line || !*line)
        return 1;
    while (*line)
    {
        if (*line != ' ' && *line != '0' && *line != '1' \
            && *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
            return 0;
        line++;
    }
    return 1;
}

static int append_line_to_map(t_map *map, char *line)
{
    int size = ft_array_size(map->map);
    char **new_map = malloc(sizeof(char *) * (size + 2));
    int i;

    if (!new_map)
        return (0);
    i = 0;
    while (i < size)
    {
        new_map[i] = map->map[i];
        i++;
    }
    new_map[size] = line;
    new_map[size + 1] = NULL;
    free(map->map);
    map->map = new_map;
    return (1);
}

int add_map_line(t_map *map, char *line)
{
    if (is_line_empty_for_map(line) && map->map)
    {
        free(line);
        return (1);
    }
    return (append_line_to_map(map, line));
}

int parse_map(t_map *map, int fd)
{
    char *line;
    int started = 0;

    map->map = NULL;
    while ((line = get_next_line(fd)))
    {
        if (!started && is_line_empty_for_map(line))
        {
            free(line);
            continue;
        }
        started = 1;
        if (!add_map_line(map, line))
            return (0);
    }
    return (map->map && map->map[0]);
}
