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
# define TEX_SIZE 64

# define KEY_ESC 65307

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

// textures
int	load_textures(t_data *data);

//utils
int		close_window(t_data *data);
void	free_array(char **array);

#endif
