/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:57:45 by douzgane          #+#    #+#             */
/*   Updated: 2025/06/18 16:49:40 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	if (assign_texture(&map->N, line, "NO") || assign_texture(&map->S, line,
			"SO") || assign_texture(&map->W, line, "WE")
		|| assign_texture(&map->E, line, "EA"))
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
