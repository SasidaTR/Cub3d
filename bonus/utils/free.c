/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:33 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/16 20:20:16 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	free_texture_paths(t_map *map)
{
	if (map->north)
	{
		free(map->north);
		map->north = NULL;
	}
	if (map->south)
	{
		free(map->south);
		map->south = NULL;
	}
	if (map->west)
	{
		free(map->west);
		map->west = NULL;
	}
	if (map->east)
	{
		free(map->east);
		map->east = NULL;
	}
}

static void	free_texture_images(t_map *map, void *mlx)
{
	if (mlx && map->tex_n)
	{
		mlx_destroy_image(mlx, map->tex_n);
		map->tex_n = NULL;
	}
	if (mlx && map->tex_s)
	{
		mlx_destroy_image(mlx, map->tex_s);
		map->tex_s = NULL;
	}
	if (mlx && map->tex_w)
	{
		mlx_destroy_image(mlx, map->tex_w);
		map->tex_w = NULL;
	}
	if (mlx && map->tex_e)
	{
		mlx_destroy_image(mlx, map->tex_e);
		map->tex_e = NULL;
	}
}

void	free_map_resources(t_map *map, void *mlx)
{
	free_texture_paths(map);
	free_texture_images(map, mlx);
	if (map->map)
	{
		free_array(map->map);
		map->map = NULL;
	}
}

void	free_all_resources(t_data *data)
{
	free_map_resources(&data->map, data->mlx);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	data->mlx = NULL;
	data->win = NULL;
}
