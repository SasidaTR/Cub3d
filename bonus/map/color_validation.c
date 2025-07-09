/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:00:00 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/09 17:07:17 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	check_rgb_format(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_rgb_range(char *str)
{
	long	value;
	int		i;

	value = 0;
	i = 0;
	if (str[0] == '+')
		i = 1;
	while (str[i])
	{
		value = value * 10 + (str[i] - '0');
		if (value > 255)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_rgb_value(char *str)
{
	if (!check_rgb_format(str))
		return (0);
	return (check_rgb_range(str));
}

int	validate_rgb_components(char **rgb, char *trimmed[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		trimmed[i] = ft_strtrim(rgb[i], " \t\n");
		if (!trimmed[i] || !is_valid_rgb_value(trimmed[i]))
		{
			if (trimmed[i])
				free(trimmed[i]);
			while (--i >= 0)
				free(trimmed[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	set_color_values(int color[3], char *trimmed[3])
{
	int	i;

	color[0] = ft_atoi(trimmed[0]);
	color[1] = ft_atoi(trimmed[1]);
	color[2] = ft_atoi(trimmed[2]);
	i = 0;
	while (i < 3)
		free(trimmed[i++]);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		return (0);
	return (1);
}
