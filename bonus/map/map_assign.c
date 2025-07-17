/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:57:17 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/17 11:36:30 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	assign_texture(char **dst, char *line, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (!ft_strncmp(line, id, len) && line[len] == ' ')
	{
		*dst = ft_strtrim(line + len + 1, " \n");
		return (1);
	}
	return (0);
}

int	assign_color(int color[3], char *line, char *id)
{
	int		len;
	char	*trimmed;

	len = ft_strlen(id);
	if (!ft_strncmp(line, id, len) && line[len] == ' ')
	{
		trimmed = ft_strtrim(line + len + 1, " \n");
		if (!trimmed)
			return (0);
		if (!parse_color(color, trimmed))
		{
			free(trimmed);
			return (0);
		}
		free(trimmed);
		return (1);
	}
	return (0);
}

int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
