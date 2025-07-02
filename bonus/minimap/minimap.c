/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:17:53 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/02 16:26:49 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	calculate_tile_size(t_map *map)
{
	int	max_dim;
	int	y;
	int	len;

	max_dim = 0;
	y = 0;
	while (map->map[y])
	{
		len = ft_strlen(map->map[y]);
		if (len > max_dim)
			max_dim = len;
		y++;
	}
	if (y > max_dim)
		max_dim = y;
	if (max_dim <= 8)
		return (18);
	else if (max_dim <= 15)
		return (10);
	else
		return (7);
}

static void	draw_map_tile(char *addr, t_data *data, int map_x, int map_y)
{
	char			c;
	int				tile_size;
	int				coords[2];
	int				color;
	t_tile_params	params;

	tile_size = calculate_tile_size(&data->map);
	c = data->map.map[map_y][map_x];
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		coords[0] = MINIMAP_MARGIN + map_x * tile_size;
		coords[1] = MINIMAP_MARGIN + map_y * tile_size;
		if (c == '1')
			color = COLOR_WALL;
		else
			color = COLOR_FLOOR;
		params.x = coords[0];
		params.y = coords[1];
		params.size = tile_size;
		params.color = color;
		draw_tile(addr, params);
	}
}

static void	draw_map_tiles(t_data *data, char *addr)
{
	int	map_y;
	int	map_x;

	map_y = 0;
	while (data->map.map[map_y])
	{
		map_x = 0;
		while (map_x < (int)ft_strlen(data->map.map[map_y]))
		{
			draw_map_tile(addr, data, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap(t_data *data, char *addr)
{
	int	tile_size;

	tile_size = calculate_tile_size(&data->map);
	draw_map_tiles(data, addr);
	draw_fov(data, addr, tile_size);
	draw_player(data, addr, tile_size);
}
