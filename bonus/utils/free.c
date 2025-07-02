/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:33 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:31 by douzgane         ###   ########.fr       */
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

void	free_map_resources(t_map *map, void *mlx)
{
	if (map->north)
		free(map->north);
	if (map->south)
		free(map->south);
	if (map->west)
		free(map->west);
	if (map->east)
		free(map->east);
	if (mlx && map->tex_n)
		mlx_destroy_image(mlx, map->tex_n);
	if (mlx && map->tex_s)
		mlx_destroy_image(mlx, map->tex_s);
	if (mlx && map->tex_w)
		mlx_destroy_image(mlx, map->tex_w);
	if (mlx && map->tex_e)
		mlx_destroy_image(mlx, map->tex_e);
	if (map->map)
		free_array(map->map);
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
