#include "../../include/cub3d.h"

// Set initial player direction
static void set_direction(t_map *map, char dir)
{
    if (dir == 'N') 
    { 
        map->dir_x = 0;
        map->dir_y = -1;
    }
    else if (dir == 'S')
    {
        map->dir_x = 0;
        map->dir_y = 1;
    }
    else if (dir == 'E')
    {
        map->dir_x = 1;
        map->dir_y = 0;
    }
    else if (dir == 'W')
    {
        map->dir_x = -1;
        map->dir_y = 0;
    }
}

static void set_camera_plane(t_map *map, char dir)
{
    if (dir == 'N')
    {
        map->plane_x = 0.66;
        map->plane_y = 0;
    }
    else if (dir == 'S')
    {
        map->plane_x = -0.66;
        map->plane_y = 0;
    }
    else if (dir == 'E')
    {
        map->plane_x = 0;
        map->plane_y = 0.66;
    }
    else if (dir == 'W')
    {
        map->plane_x = 0;
        map->plane_y = -0.66;
    }
}

static int find_player(t_map *map)
{
    int i;
    int j;
    char c;

    i = 0;
    while (map->map && map->map[i])
    {
        j = 0;
        while (map->map[i][j])
        {
            c = map->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                map->player_x = j + 0.5;
                map->player_y = i + 0.5;
                set_direction(map, c);
                set_camera_plane(map, c);
                map->map[i][j] = '0';
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

static int has_extra_players(t_map *map)
{
    int i;
    int j;
    char c;

    i = 0;
    while (map->map && map->map[i])
    {
        j = 0;
        while (map->map[i][j])
        {
            c = map->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int	check_map_validity(t_map *map)
{
    if (!find_player(map))
        return (0);
    if (has_extra_players(map))
        return (0);
    return (1);
}
