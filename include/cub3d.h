#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define TEX_SIZE 64

// Minimap constants
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_Q 113

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.1

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	wall_x;
	double	wall_y;  // Nouvelle variable pour stocker la coordonnée y du point d'impact
	double	step;
	double	tex_pos;
}	t_ray;

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
	void	*tex_floor;    // Texture pour le sol (gazon)
	void	*tex_ceiling;  // Texture pour le plafond (ciel)
	char	*tex_data_n;
	char	*tex_data_s;
	char	*tex_data_w;
	char	*tex_data_e;
	char	*tex_data_floor;    // Données de texture pour le sol
	char	*tex_data_ceiling;  // Données de texture pour le plafond
	int		tex_width;
	int		tex_height;
	int		tex_n_bpp;
	int		tex_n_line_length;
	int			tex_n_endian;
	int		tex_s_bpp;
	int		tex_s_line_length;
	int		tex_s_endian;
	int		tex_w_bpp;
	int		tex_w_line_length;
	int		tex_w_endian;
	int		tex_e_bpp;
	int		tex_e_line_length;
	int		tex_e_endian;
	// Dynamic minimap parameters
	int	minimap_scale;
	int	minimap_w;
	int	minimap_h;
	int	minimap_x;
	int	minimap_y;
}	t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	map;
	t_keys	keys;
}	t_data;

/* main.c */
void	setup_event_hooks(t_data *data);

/* init.c */
void	init_data(t_data *data);
int		load_resources(t_data *data, char *map_file);

/* input.c */
int		handle_key(int keycode, t_data *data);
int		handle_key_release(int keycode, t_data *data);
void	process_movement(t_data *data);

/* movement.c */
void	handle_rotation(t_data *data);
void	calc_move(t_data *data, double *move_x, double *move_y);
void	apply_move(t_data *data, double move_x, double move_y);

/* rotation.c */
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

/* map.c */
void	display_map(t_data *data);

/* collision.c */
int		check_wall_collision(t_data *data, double new_x, double new_y);

/* parsing/validation.c */
int		validate_extension(char *file);
int		is_config_complete(t_map *map);

/* parsing/load_map.c */
int		load_map(char *file, t_map *map);

/* parsing/reader.c */
int		read_config(t_map *map, int fd);

/* parsing/mapper.c */
int		parse_map(t_map *map, int fd);

/* parsing/player.c */
int		check_map_validity(t_map *map);

/* parsing/parser.c */
int		parse_line(t_map *map, char *line);

/* parsing/texture_parser.c */
int		parse_textures(t_map *map, char *line, char *id);

/* parsing/color_parser.c */
int		parse_colors(t_map *map, char *line, char id);

/* raycasting.c */
void	init_ray(t_ray *ray, t_data *data, int x);
void	calculate_ray(t_ray *ray, t_data *data);
void	perform_dda(t_ray *ray, t_data *data);
void	calculate_wall_height(t_ray *ray, t_data *data);

/* dda_utils.c */
void	advance_ray(t_ray *ray);
int		is_valid_position(t_ray *ray, t_data *data);
int		check_wall_hit(t_ray *ray, t_data *data);

/* raycasting_utils.c */
void	draw_vertical_line(t_data *data, t_ray *ray, int x);
void	draw_walls(t_data *data, t_ray *ray, int x);

/* texture_manager.c */
int		load_textures(t_data *data);

/* texture_loader.c */
int		validate_texture_file(char *path);
void	*load_single_texture(t_data *data, char *path, int *w, int *h);

/* texture_data.c */
int		load_texture_data(t_data *data);

/* texture_calc.c */
void	calculate_wall_texture(t_ray *ray, t_data *data);

/* texture_render.c */
int		get_texture_color(t_ray *ray, t_data *data);

/* minimap functions */
void    draw_minimap(t_data *data);
void    draw_minimap_fov(t_data *data);
void    draw_minimap_player(t_data *data);
void	draw_minimap_walls(t_data *data, char **map, int rows, int cols);
void	calculate_minimap_params(t_data *data, int rows, int cols);

/* utils.c */
void	free_array(char **array);
int		ft_array_size(char **array);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int		close_window(t_data *data);

#endif
