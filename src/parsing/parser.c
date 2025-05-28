#include "../../include/cub3d.h"

static char *skip_whitespace(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return (line);
}

static int is_empty_line(char *line)
{
    while (*line)
    {
        if (*line != ' ' && *line != '\t' && *line != '\r' && *line != '\n')
            return (0);
        line++;
    }
    return (1);
}

static int dispatch_parse(t_map *map, char *line)
{
    if ((line[0] == 'N' && line[1] == 'O') || (line[0] == 'S' && line[1] == 'O')
        || (line[0] == 'W' && line[1] == 'E') || (line[0] == 'E' && line[1] == 'A'))
        return (parse_textures(map, line, line));
    if (line[0] == 'F' || line[0] == 'C')
        return (parse_colors(map, line, line[0]));
    return (0);
}

int parse_line(t_map *map, char *line)
{
    char *trim = skip_whitespace(line);
    if (is_empty_line(trim))
        return (1);
    return (dispatch_parse(map, trim));
}
