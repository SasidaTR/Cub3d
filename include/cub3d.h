#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define TEX_SIZE 1024

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define MOVE_SPEED 0.005
# define ROT_SPEED 0.005

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
}	t_ray;

typedef struct s_map
{
	char	**map;
	char	*N;
	char	*S;
	char	*W;
	char	*E;
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
}	t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	map;
	int		keys[65536];
}	t_data;

// input
int		handle_key(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	update_player(t_data *data);

// map
int		load_map(char *file, t_map *map);
void	display_map(t_data *data);

// raycasting
int		get_tex_pixel(void *tex, int x, int y);
void	render_column(t_data *data, char *addr, int x);
void	draw_ceiling(t_data *d, char *addr, int x, int limit);
void	draw_floor(t_data *d, char *addr, int x, int start);
void	draw_wall(t_ray *r, char *addr, int x);

// textures
int		load_textures(t_data *data);

// utils
int		close_window(t_data *data);
void	free_array(char **array);

#endif
