#include "../../include/cub3d.h"
#include <fcntl.h>
#include <unistd.h>

// Load and parse .cub map using external parsing modules
int	load_map(char *file, t_map *map)
{
    int fd;

    if (!validate_extension(file))
        return (0);
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (0);

    map->north = NULL;
    map->south = NULL;
    map->west = NULL;
    map->east = NULL;
    map->floor[0] = -1;
    map->ceiling[0] = -1;

    if (!read_config(map, fd) || !parse_map(map, fd))
    {
        close(fd);
        return (0);
    }
    close(fd);

    if (!check_map_validity(map))
        return (0);
    return (1);
}
