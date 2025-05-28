#include "../../include/cub3d.h"

int validate_extension(char *file)
{
    int len = ft_strlen(file);
    if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
    {
        ft_putstr_fd("Error: Invalid file extension\n", 2);
        return (0);
    }
    return (1);
}

int is_config_complete(t_map *map)
{
    return map->north && map->south && map->west && map->east
           && map->floor[0] >= 0 && map->ceiling[0] >= 0;
}
