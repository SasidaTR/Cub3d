/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:57:52 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/15 17:42:20 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_closed(char **map)
{
	if (!map || !map[0])
		return (0);
	if (!check_first_line(map))
		return (0);
	if (!check_last_line(map))
		return (0);
	if (!check_middle_lines(map))
		return (0);
	return (1);
}

int	validate_map_chars(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr("01NSEW \n", map[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map_empty_lines(char **map)
{
	int	y;
	int	map_started;
	int	j;

	y = 0;
	map_started = 0;
	while (map[y])
	{
		if (!is_empty_line(map[y]))
			map_started = 1;
		else if (map_started)
		{
			j = y + 1;
			while (map[j])
			{
				if (!is_empty_line(map[j]))
					return (0);
				j++;
			}
		}
		y++;
	}
	return (1);
}
