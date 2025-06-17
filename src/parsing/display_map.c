#include "../../include/cub3d.h"

void	display_map(t_data *d)
{
	void	*img;
	char	*addr;
	int		bpp;
	int		sl;
	int		endian;
	int		x;

	img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	addr = mlx_get_data_addr(img, &bpp, &sl, &endian);
	x = 0;
	while (x < WIDTH)
		render_column(d, addr, x++);
	mlx_put_image_to_window(d->mlx, d->win, img, 0, 0);
	mlx_destroy_image(d->mlx, img);
}
