/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:45:00 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/17 10:49:17 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	process_rgb_char(char c, int *comma_count, int *number_count,
		int *in_number)
{
	if (ft_isdigit(c))
	{
		if (!*in_number)
		{
			(*number_count)++;
			*in_number = 1;
		}
	}
	else if (c == ',')
	{
		if (!*in_number || *comma_count >= 2)
			return (0);
		(*comma_count)++;
		*in_number = 0;
	}
	else if (c != ' ' && c != '\t')
		return (0);
	return (1);
}

static int	is_strict_rgb_format(char *line)
{
	int	i;
	int	comma_count;
	int	number_count;
	int	in_number;

	i = 0;
	comma_count = 0;
	number_count = 0;
	in_number = 0;
	while (line[i])
	{
		if (!process_rgb_char(line[i], &comma_count, &number_count, &in_number))
			return (0);
		i++;
	}
	return (comma_count == 2 && number_count == 3 && in_number);
}

int	parse_color(int color[3], char *line)
{
	char	**rgb;
	char	*trimmed[3];

	if (!is_strict_rgb_format(line))
		return (0);
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_array(rgb), 0);
	if (!validate_rgb_components(rgb, trimmed))
		return (free_array(rgb), 0);
	if (!set_color_values(color, trimmed))
	{
		free_array(rgb);
		return (0);
	}
	free_array(rgb);
	return (1);
}
