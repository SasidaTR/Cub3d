/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:57:04 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/15 17:49:52 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	file_exists(char *path)
{
	int	fd;

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
	if (!file_exists(map->north) || !file_exists(map->south)
		|| !file_exists(map->west) || !file_exists(map->east))
		return (0);
	return (1);
}

int	validate_required_elements(t_map *map)
{
	if (!map->north || !map->south || !map->west || !map->east)
		return (0);
	if (map->floor[0] == -1 || map->floor[1] == -1 || map->floor[2] == -1)
		return (0);
	if (map->ceiling[0] == -1 || map->ceiling[1] == -1 || map->ceiling[2] == -1)
		return (0);
	return (1);
}
