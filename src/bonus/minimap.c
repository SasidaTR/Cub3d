/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:50:26 by douzgane          #+#    #+#             */
/*   Updated: 2025/06/25 11:56:01 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Couleurs de la minimap
#define COLOR_WALL 0xFFFFFF
#define COLOR_FLOOR 0x404040
#define COLOR_PLAYER 0xFF0000
#define COLOR_FOV 0x00FFFF

// Calcule la taille d'une tuile selon la dimension max de la map
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

// Dessine un pixel avec transparence
static void	put_pixel(char *addr, int x, int y, int color)
{
	int	offset;
	int	bg_color;
	int	blended_color;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = y * WIDTH * 4 + x * 4;
	bg_color = *(int *)(addr + offset);
	blended_color = ((int)(((bg_color >> 16) & 0xFF) * (1.0 - MINIMAP_ALPHA)
				+ ((color >> 16) & 0xFF) * MINIMAP_ALPHA)) << 16;
	blended_color |= ((int)(((bg_color >> 8) & 0xFF) * (1.0 - MINIMAP_ALPHA)
				+ ((color >> 8) & 0xFF) * MINIMAP_ALPHA)) << 8;
	blended_color |= (int)((bg_color & 0xFF) * (1.0 - MINIMAP_ALPHA)
			+ (color & 0xFF) * MINIMAP_ALPHA);
	*(int *)(addr + offset) = blended_color;
}

// Dessine une tuile carrée
static void	draw_tile(char *addr, int x, int y, int size, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < size)
	{
		dx = 0;
		while (dx < size)
		{
			put_pixel(addr, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

// Structure pour les paramètres de la ligne
typedef struct s_line_params
{
	int					dx;
	int					dy;
	int					sx;
	int					sy;
}						t_line_params;

// Initialise les paramètres de la ligne
static t_line_params	init_line_params(int x0, int y0, int x1, int y1)
{
	t_line_params	params;

	params.dx = abs(x1 - x0);
	params.dy = abs(y1 - y0);
	if (x0 < x1)
		params.sx = 1;
	else
		params.sx = -1;
	if (y0 < y1)
		params.sy = 1;
	else
		params.sy = -1;
	return (params);
}

// Dessine une ligne (Bresenham)
static void	draw_line(char *addr, int x0, int y0, int x1, int y1, int color)
{
	t_line_params	p;
	int				err;
	int				e2;

	p = init_line_params(x0, y0, x1, y1);
	err = p.dx - p.dy;
	while (1)
	{
		put_pixel(addr, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -p.dy)
		{
			err -= p.dy;
			x0 += p.sx;
		}
		if (e2 < p.dx)
		{
			err += p.dx;
			y0 += p.sy;
		}
	}
}

// Structure pour les paramètres du FOV
typedef struct s_fov_params
{
	int					center_x;
	int					center_y;
	int					fov_len;
	double				left_x;
	double				left_y;
	double				right_x;
	double				right_y;
}						t_fov_params;

// Initialise les paramètres du FOV
static t_fov_params	init_fov_params(t_data *data, int tile_size)
{
	t_fov_params	params;
	double			len_left;
	double			len_right;

	params.center_x = MINIMAP_MARGIN + (int)(data->map.player_x * tile_size);
	params.center_y = MINIMAP_MARGIN + (int)(data->map.player_y * tile_size);
	params.fov_len = tile_size * 2;
	params.left_x = data->map.dir_x - data->map.plane_x;
	params.left_y = data->map.dir_y - data->map.plane_y;
	params.right_x = data->map.dir_x + data->map.plane_x;
	params.right_y = data->map.dir_y + data->map.plane_y;
	len_left = sqrt(params.left_x * params.left_x + params.left_y
			* params.left_y);
	len_right = sqrt(params.right_x * params.right_x + params.right_y
			* params.right_y);
	params.left_x /= len_left;
	params.left_y /= len_left;
	params.right_x /= len_right;
	params.right_y /= len_right;
	return (params);
}

// Dessine le champ de vision (2 lignes aux extrémités)
static void	draw_fov(t_data *data, char *addr, int tile_size)
{
	t_fov_params	p;

	p = init_fov_params(data, tile_size);
	draw_line(addr, p.center_x, p.center_y, p.center_x + (int)(p.left_x
			* p.fov_len), p.center_y + (int)(p.left_y * p.fov_len), COLOR_FOV);
	draw_line(addr, p.center_x, p.center_y, p.center_x + (int)(p.right_x
			* p.fov_len), p.center_y + (int)(p.right_y * p.fov_len), COLOR_FOV);
}

// Dessine une tuile de la map selon son type
static void	draw_map_tile(char *addr, t_data *data, int map_x, int map_y)
{
	char	c;
	int		tile_size;
	int		coords[2];
	int		color;

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
		draw_tile(addr, coords[0], coords[1], tile_size, color);
	}
}

// Dessine toutes les tuiles de la map
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

// Dessine le joueur et sa direction
static void	draw_player(t_data *data, char *addr, int tile_size)
{
	int	player_pos[2];
	int	center_pos[2];
	int	dir_end[2];

	player_pos[0] = MINIMAP_MARGIN + (int)(data->map.player_x * tile_size) - 2;
	player_pos[1] = MINIMAP_MARGIN + (int)(data->map.player_y * tile_size) - 2;
	draw_tile(addr, player_pos[0], player_pos[1], 5, COLOR_PLAYER);
	center_pos[0] = player_pos[0] + 2;
	center_pos[1] = player_pos[1] + 2;
	dir_end[0] = center_pos[0] + (int)(data->map.dir_x * tile_size * 0.7);
	dir_end[1] = center_pos[1] + (int)(data->map.dir_y * tile_size * 0.7);
	draw_line(addr, center_pos[0], center_pos[1], dir_end[0], dir_end[1],
		COLOR_PLAYER);
}

// Fonction principale pour dessiner la minimap
void	draw_minimap(t_data *data, char *addr)
{
	int	tile_size;

	tile_size = calculate_tile_size(&data->map);
	draw_map_tiles(data, addr);
	draw_fov(data, addr, tile_size);
	draw_player(data, addr, tile_size);
}
