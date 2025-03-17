#include "../../include/cub3d.h"

void	display_map(t_data *data)
{
	int		x;
	int		y;
	int		color;
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;

	img = mlx_new_image(data->mlx, 800, 600);
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			color = data->map.floor;
			if (y < 300)
				color = data->map.ceiling;
			*(int *)(addr + (y * size_line + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}

int	parse_color(int *dst, char *str)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (0);
	dst[0] = ft_atoi(rgb[0]);
	dst[1] = ft_atoi(rgb[1]);
	dst[2] = ft_atoi(rgb[2]);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	return (1);
}

int	parse_map(t_map *map, char **lines)
{
	int	i;

	i = 0;
	while (lines[i] != NULL)
	{
		if (!ft_strncmp(lines[i], "C ", 2))
		{
			if (!parse_color(map->ceiling, lines[i] + 2))
				return (0);
		}
		else if (!ft_strncmp(lines[i], "F ", 2))
		{
			if (!parse_color(map->floor, lines[i] + 2))
				return (0);
		}
		i++;
	}
	return (1);
}

int	load_map(char *file, t_map *map)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	*full_map;
	char	**lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	full_map = ft_strdup("");
	if (!full_map)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = full_map;
		full_map = ft_strjoin(full_map, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	lines = ft_split(full_map, '\n');
	free(full_map);
	if (!lines)
		return (0);
	if (!parse_map(map, lines))
		return (0);
	return (1);
}
