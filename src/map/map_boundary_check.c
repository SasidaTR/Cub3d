/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_boundary_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:50:00 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/17 11:09:46 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_invalid_adjacent(char **map, int y, int x)
{
	if (!map[y - 1] || x >= (int)ft_strlen(map[y - 1]) || map[y - 1][x] == ' '
		|| map[y - 1][x] == '\n')
		return (1);
	if (!map[y + 1] || x >= (int)ft_strlen(map[y + 1]) || map[y + 1][x] == ' '
		|| map[y + 1][x] == '\n')
		return (1);
	if (x == 0 || map[y][x - 1] == ' ' || map[y][x - 1] == '\n')
		return (1);
	if (!map[y][x + 1] || map[y][x + 1] == ' ' || map[y][x + 1] == '\n')
		return (1);
	return (0);
}

int	check_first_line(char **map)
{
	int	x;

	x = 0;
	while (map[0][x])
	{
		if (map[0][x] == '0' || ft_strchr("NSEW", map[0][x]))
			return (0);
		x++;
	}
	return (1);
}

int	check_last_line(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y + 1])
		y++;
	x = 0;
	while (map[y][x])
	{
		if (map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
			return (0);
		x++;
	}
	return (1);
}

int	check_middle_lines(char **map)
{
	int	y;
	int	x;

	y = 1;
	while (map[y + 1])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
				&& is_invalid_adjacent(map, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
