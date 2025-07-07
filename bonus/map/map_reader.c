/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:57:45 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	read_map_lines(int fd, char ***lines, int *size)
{
	char	*line;
	char	**tmp;

	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_realloc(*lines, (*size) * sizeof(char *), (*size + 2)
				* sizeof(char *));
		if (!tmp)
			return (free(line), 0);
		*lines = tmp;
		(*lines)[(*size)++] = line;
		(*lines)[*size] = NULL;
		line = get_next_line(fd);
	}
	return (1);
}

static int	handle_map_line(char *line, t_map *map, char ***lines, int *size)
{
	if ((ft_strncmp(line, "NO", 2) == 0 && map->north)
		|| (ft_strncmp(line, "SO", 2) == 0 && map->south)
		|| (ft_strncmp(line, "EA", 2) == 0 && map->east)
		|| (ft_strncmp(line, "WE", 2) == 0 && map->west)
		|| (ft_strncmp(line, "F", 1) == 0 && map->floor[0] != -1)
		|| (ft_strncmp(line, "C", 1) == 0 && map->ceiling[0] != -1))
		return (-1);
	if (assign_texture(&map->north, line, "NO") || assign_texture(&map->south,
			line, "SO") || assign_texture(&map->west, line, "WE")
		|| assign_texture(&map->east, line, "EA"))
		return (0);
	else if (assign_color(map->floor, line, "F"))
		return (0);
	else if (assign_color(map->ceiling, line, "C"))
		return (0);
	else if (ft_strchr(line, '1'))
	{
		*lines = ft_calloc(2, sizeof(char *));
		if (!*lines)
			return (-1);
		(*lines)[0] = line;
		*size = 1;
		return (1);
	}
	return (0);
}

int	read_map_start(int fd, t_map *map, char ***lines, int *size)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line)
	{
		result = handle_map_line(line, map, lines, size);
		if (result > 0)
			return (1);
		if (result < 0)
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
