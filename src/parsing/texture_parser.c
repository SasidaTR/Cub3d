#include "../../include/cub3d.h"
#include <stdlib.h>

// Assign texture file path based on identifier
static int assign_texture_path(t_map *map, char *path, const char *id)
{
    if ((id[0] == 'N' && id[1] == 'O') || (id[0] == 'N' && id[1] == '\0'))
        map->north = path;
    else if ((id[0] == 'S' && id[1] == 'O') || (id[0] == 'S' && id[1] == '\0'))
        map->south = path;
    else if ((id[0] == 'W' && id[1] == 'E') || (id[0] == 'W' && id[1] == '\0'))
        map->west = path;
    else if ((id[0] == 'E' && id[1] == 'A') || (id[0] == 'E' && id[1] == '\0'))
        map->east = path;
    else
    {
        free(path);
        return (0);
    }
    return (1);
}

// Public: parse texture path line (NO, SO, WE, EA)
int parse_textures(t_map *map, char *line, char *id)
{
    char *path;
    int offset;

    if (line[1] == ' ')
        offset = 2;
    else
        offset = 3;
    path = ft_strtrim(line + offset, " \t\n\r\f\v");
    if (!path)
        return (0);
    return (assign_texture_path(map, path, id));
}
