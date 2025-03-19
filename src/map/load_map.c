#include "../../include/cub3d.h"

int	validate_and_store_rgb(int *dst, char **rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!rgb[i])
			return (0);
		dst[i] = ft_atoi(rgb[i]);
		free(rgb[i]);
		i++;
	}
	free(rgb);
	return (1);
}

int	parse_color(int *dst, char *str)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (0);
	if (!validate_and_store_rgb(dst, rgb))
	{
		free(rgb);
		return (0);
	}
	return (1);
}

int	parse_textures(t_map *map, char *line)
{
	if (!ft_strncmp(line, "N ", 2))
		map->N = ft_strdup(line + 2);
	else if (!ft_strncmp(line, "S ", 2))
		map->S = ft_strdup(line + 2);
	else if (!ft_strncmp(line, "W ", 2))
		map->W = ft_strdup(line + 2);
	else if (!ft_strncmp(line, "E ", 2))
		map->E = ft_strdup(line + 2);
	else
		return (0);
	return (1);
}

void	find_player(t_map *map, int y, int x, char dir)
{
	map->player_x = x;
	map->player_y = y;
	map->player_dir = dir;
}

int	parse_map_data(t_map *map, char **lines, int i)
{
	int	x;
	int	y;

	y = 0;
	map->map = ft_calloc(ft_array_size(lines + i) + 1, sizeof(char *));
	if (!map->map)
		return (0);
	while (lines[i])
	{
		map->map[y] = ft_strdup(lines[i]);
		if (!map->map[y])
			return (0);
		x = 0;
		while (map->map[y][x])
		{
			if (ft_strchr("NSWE", map->map[y][x]))
				find_player(map, y, x, map->map[y][x]);
			x++;
		}
		y++;
		i++;
	}
	return (1);
}

int	parse_map(t_map *map, char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && !ft_isdigit(lines[i][0]))
	{
		if (!parse_color(map->ceiling, lines[i] + 2) && !parse_color(map->floor, lines[i] + 2)
			&& !parse_textures(map, lines[i]))
			return (0);
		i++;
	}
	if (!lines[i] || !parse_map_data(map, lines, i))
		return (0);
	return (1);
}

char	*read_full_map(int fd)
{
	char	*line;
	char	*tmp;
	char	*full_map;

	full_map = ft_strdup("");
	if (!full_map)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = full_map;
		full_map = ft_strjoin(full_map, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	return (full_map);
}

int	load_textures(t_data *data)
{
	data->map.tex_n = mlx_xpm_file_to_image(data->mlx, data->map.N, &(int){64}, &(int){64});
	data->map.tex_s = mlx_xpm_file_to_image(data->mlx, data->map.S, &(int){64}, &(int){64});
	data->map.tex_w = mlx_xpm_file_to_image(data->mlx, data->map.W, &(int){64}, &(int){64});
	data->map.tex_e = mlx_xpm_file_to_image(data->mlx, data->map.E, &(int){64}, &(int){64});
	if (!data->map.tex_n || !data->map.tex_s || !data->map.tex_w || !data->map.tex_e)
		return (0);
	return (1);
}

int	load_map(char *file, t_map *map)
{
	int		fd;
	char	*full_map;
	char	**lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	full_map = read_full_map(fd);
	close(fd);
	if (!full_map)
		return (0);
	lines = ft_split(full_map, '\n');
	free(full_map);
	if (!lines)
		return (0);
	if (!parse_map(map, lines))
	{
		free_array(lines);
		return (0);
	}
	free_array(lines);
	return (1);
}
