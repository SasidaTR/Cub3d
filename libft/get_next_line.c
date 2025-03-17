#include "get_next_line.h"

char	*read_line(int fd, char *save)
{
	char	buf[BUFFER_SIZE + 1];
	int		rd;

	rd = 1;
	while (!gnl_strchr(save, '\n') && rd > 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free(save);
			return (NULL);
		}
		buf[rd] = '\0';
		save = gnl_strjoin(save, buf);
	}
	return (save);
}

char	*extract_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_next(char *save)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new = malloc(gnl_strlen(save) - i + 1);
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		new[j++] = save[i++];
	new[j] = '\0';
	free(save);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_line(fd, save);
	if (!save)
		return (NULL);
	line = extract_line(save);
	save = ft_next(save);
	return (line);
}
