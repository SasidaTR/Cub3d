/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:10:00 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/09 16:06:24 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_empty_or_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_element_line(char *line)
{
	if (is_empty_or_whitespace(line))
		return (1);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (1);
	if (ft_strchr(line, '1') || ft_strchr(line, '0')
		|| ft_strchr(line, 'N') || ft_strchr(line, 'S')
		|| ft_strchr(line, 'E') || ft_strchr(line, 'W'))
		return (1);
	return (0);
}

int	is_invalid_line_or_duplicate(char *line, t_map *map)
{
	if (!is_valid_element_line(line))
		return (1);
	if ((*line != '\0' && *line != '\n'
			&& ft_strncmp(line, "NO", 2) && ft_strncmp(line, "SO", 2)
			&& ft_strncmp(line, "WE", 2) && ft_strncmp(line, "EA", 2)
			&& ft_strncmp(line, "F", 1) && ft_strncmp(line, "C", 1)
			&& !ft_strchr(line, '1'))
		|| (ft_strncmp(line, "NO", 2) == 0 && map->north)
		|| (ft_strncmp(line, "SO", 2) == 0 && map->south)
		|| (ft_strncmp(line, "EA", 2) == 0 && map->east)
		|| (ft_strncmp(line, "WE", 2) == 0 && map->west)
		|| (ft_strncmp(line, "F", 1) == 0 && map->floor[0] != -1)
		|| (ft_strncmp(line, "C", 1) == 0 && map->ceiling[0] != -1))
		return (1);
	return (0);
}
