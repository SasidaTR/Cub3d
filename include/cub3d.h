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
	int		ceiling[3];
	int		floor[3];
	char	**map;
}	t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	map;
}	t_data;

// init
int		load_map(char *file, t_map *map);

// input
int		handle_key(int keycode, t_data *data);

// parsing

//utils
int		close_window(t_data *data);

void	display_map(t_data *data);

#endif
