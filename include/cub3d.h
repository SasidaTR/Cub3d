#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY_ESC 65307

typedef struct s_map
{
	char	*N;
	char	*S;
	char	*W;
	char	*E;
	void	*tex_n;
	void	*tex_s;
	void	*tex_w;
	void	*tex_e;
	int		ceiling[3];
	int		floor[3];
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	map;
}	t_data;

// map
int		load_map(char *file, t_map *map);
void	display_map(t_data *data);
int	load_textures(t_data *data);

// input
int		handle_key(int keycode, t_data *data);

// parsing

//utils
int		close_window(t_data *data);
void	free_array(char **array);

#endif
