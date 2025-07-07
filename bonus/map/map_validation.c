/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:57:52 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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
	int		y;
	int		x;
	int		line_len;
	char	c;

	y = 0;
	while (map[y])
	{
		x = 0;
		line_len = ft_strlen(map[y]) - 1;
		if (map[y][line_len] == '\n')
			line_len--;
		c = map[y][x];
		while (c && c != '\n')
		{
			if (c == '0' || ft_strchr("NSWE", c))
			{
				if (y == 0 || !map[y + 1] || x == 0 || x == line_len)
					return (0);
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
					return (0);
			}
			x++;
			c = map[y][x];
		}
		y++;
	}
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
