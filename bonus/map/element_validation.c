/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:57:04 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/17 11:50:25 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	file_exists_and_valid_xpm(char *path)
{
	int	fd;
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".xpm") != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_textures(t_map *map)
{
	if (!map->north || !map->south || !map->west || !map->east)
		return (0);
	if (!file_exists_and_valid_xpm(map->north)
		|| !file_exists_and_valid_xpm(map->south)
		|| !file_exists_and_valid_xpm(map->west)
		|| !file_exists_and_valid_xpm(map->east))
		return (0);
	return (1);
}

int	validate_required_elements(t_map *map)
{
	if (!map->north || !map->south || !map->west || !map->east)
		return (0);
	if (map->floor[0] < 0 || map->floor[0] > 255
		|| map->floor[1] < 0 || map->floor[1] > 255
		|| map->floor[2] < 0 || map->floor[2] > 255)
		return (0);
	if (map->ceiling[0] < 0 || map->ceiling[0] > 255
		|| map->ceiling[1] < 0 || map->ceiling[1] > 255
		|| map->ceiling[2] < 0 || map->ceiling[2] > 255)
		return (0);
	return (1);
}
