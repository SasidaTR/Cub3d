/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:46 by douzgane          #+#    #+#             */
/*   Updated: 2025/06/18 16:49:40 by douzgane         ###   ########.fr       */
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
	map->N = NULL;
	map->S = NULL;
	map->E = NULL;
	map->W = NULL;
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

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, main_loop, data);
}

static int	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (printf("Error\nFailed to initialize MLX\n"), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Usage: ./cub3D <map.cub>\n"), 1);
	ft_bzero(&data, sizeof(t_data));
	init_map(&data.map);
	if (!load_map(argv[1], &data.map))
		return (1);
	if (!initialize_mlx(&data))
		return (free_map_resources(&data.map, NULL), 1);
	if (!load_textures(&data))
		return (free_map_resources(&data.map, data.mlx),
			mlx_destroy_display(data.mlx), free(data.mlx),
			printf("Error\nFailed to load textures\n"), 1);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data.win)
		return (free_all_resources(&data),
			printf("Error\nFailed to create window\n"), 1);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	free_all_resources(&data);
	return (0);
}

