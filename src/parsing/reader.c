#include "../../include/cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	parse_line(t_map *map, char *line);

// Read configuration lines (textures/colors) until all are set
int	read_config(t_map *map, int fd)
{
    char *line;
    int result;

    while ((line = get_next_line(fd)) && !is_config_complete(map))
    {
        result = parse_line(map, line);
        free(line);
        if (!result)
            return (0);
    }
    if (line)
        free(line);
    return (is_config_complete(map));
}
