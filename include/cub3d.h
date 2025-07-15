/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:19:56 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/15 17:42:20 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1200
# define HEIGHT 800
# define TEX_SIZE 1024

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define MOVE_SPEED 0.01
# define ROT_SPEED 0.01

# define COLOR_WALL 0xFFFFFF
# define COLOR_FLOOR 0x404040
# define COLOR_PLAYER 0xFF0000
# define COLOR_FOV 0x00FFFF
# define MINIMAP_SIZE 150
# define MINIMAP_MARGIN 15
# define MINIMAP_ALPHA 0.95

typedef struct s_line_params
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
}			t_line_params;

typedef struct s_fov_params
{
	int		center_x;
	int		center_y;
	int		fov_len;
	double	left_x;
	double	left_y;
	double	right_x;
	double	right_y;
}			t_fov_params;

typedef struct s_ray
{
	double	cam;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	side_x;
	double	side_y;
	int		side;
	double	dist;
	int		line_height;
	int		start;
	int		end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	void	*tex;
}			t_ray;

typedef struct s_map
{
	char	**map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[3];
	int		ceiling[3];
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	void	*tex_n;
	void	*tex_s;
	void	*tex_w;
	void	*tex_e;
}			t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	map;
	int		keys[65536];
}			t_data;

// input
int			handle_key(int keycode, t_data *data);
int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);
void		update_player(t_data *data);
int			close_window(t_data *data);
int			check_wall_collision(t_data *data, double new_x, double new_y);

// map
int			load_map(char *path, t_map *map);
int			read_map_start(int fd, t_map *map, char ***lines, int *size);
int			read_map_lines(int fd, char ***lines, int *size);
int			assign_texture(char **dst, char *line, char *id);
int			assign_color(int color[3], char *line, char *id);
int			validate_textures(t_map *map);
int			validate_required_elements(t_map *map);
int			validate_map_empty_lines(char **map);
int			validate_map_chars(char **map);
int			is_map_closed(char **map);
int			is_invalid_adjacent(char **map, int y, int x);
int			check_first_line(char **map);
int			check_last_line(char **map);
int			check_middle_lines(char **map);
int			parse_map_data(t_map *map, char **lines, int i);
void		init_player(t_map *map, int y, int x, char dir);
int			parse_color(int color[3], char *line);
int			validate_rgb_components(char **rgb, char *trimmed[3]);
int			set_color_values(int color[3], char *trimmed[3]);
int			is_valid_rgb_value(char *str);
int			check_rgb_format(char *str);
int			check_rgb_range(char *str);
void		display_map(t_data *data);
int			is_empty_or_whitespace(char *line);
int			is_valid_element_line(char *line);
int			is_invalid_line_or_duplicate(char *line, t_map *map);

// raycasting
int			get_tex_pixel(void *tex, int x, int y);
void		render_column(t_data *data, char *addr, int x);
void		draw_ceiling(t_data *d, char *addr, int x, int limit);
void		draw_floor(t_data *d, char *addr, int x, int start);
void		draw_wall(t_ray *r, char *addr, int x);
void		run_dda(t_ray *r, char **map);
void		project_wall(t_ray *r, t_data *d);
void		select_tex(t_ray *r, t_data *d);

// textures
int			load_textures(t_data *data);

// utils
void		free_array(char **array);
int			print_error(char *msg);
void		free_map_resources(t_map *map, void *mlx);
void		free_all_resources(t_data *data);

#endif
