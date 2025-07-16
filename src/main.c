/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:46 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/16 18:55:04 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main_loop(t_data *data)
{
	update_player(data);
	display_map(data);
	return (0);
}

void	init_map(t_map *map)
{
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
	map->map = NULL;
	map->player_x = 0;
	map->player_y = 0;
	map->dir_x = 0;
	map->dir_y = 0;
	map->plane_x = 0;
	map->plane_y = 0;
	map->floor[0] = -1;
	map->floor[1] = -1;
	map->floor[2] = -1;
	map->ceiling[0] = -1;
	map->ceiling[1] = -1;
	map->ceiling[2] = -1;
}

int	init_game_data(int argc, char **argv, t_data *data)
{
	if (!validate_arguments(argc, argv))
		return (0);
	ft_bzero(data, sizeof(t_data));
	init_map(&data->map);
	if (!load_map(argv[1], &data->map))
		return (free_map_resources(&data->map, NULL), 0);
	if (!initialize_mlx(data))
		return (free_map_resources(&data->map, NULL), 0);
	return (1);
}

int	setup_graphics(t_data *data)
{
	if (!load_textures(data))
		return (free_map_resources(&data->map, data->mlx),
			mlx_destroy_display(data->mlx), free(data->mlx),
			ft_printf("Error: Texture loading failed\n"
				"Check if all texture files (.xpm) exist and are valid\n"),
			0);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (free_all_resources(data),
			ft_printf("Error: Window creation failed\n"
				"Insufficient memory or display resources\n"),
			0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_game_data(argc, argv, &data))
		return (1);
	if (!setup_graphics(&data))
		return (1);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	free_all_resources(&data);
	return (0);
}
