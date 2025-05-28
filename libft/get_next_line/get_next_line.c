/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:03:22 by douzgane          #+#    #+#             */
/*   Updated: 2025/05/26 13:26:45 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

void	ft_free(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}

static char	*read_line(int fd, char *buffer, char *str)
{
	int		read_bytes;
	char	*temp;

	read_bytes = 1;
	if (str == NULL)
		str = ft_strdup("");
	while (!ft_strchr(str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			ft_free((void **)&str);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		temp = str;
		str = ft_strjoin(str, buffer);
		free(temp);
		if (!str)
			return (NULL);
	}
	return (str);
}

static char	*extract_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i] || !str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*save_remaining(char *str)
{
	char	*remaining;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	remaining = (char *)malloc(ft_strlen(str) - i + 1);
	if (!remaining)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		remaining[j++] = str[i++];
	remaining[j] = '\0';
	ft_free((void **)&str);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
	{
		if (str != NULL)
			ft_free((void **)&str);
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		ft_free((void **)&str);
		return (NULL);
	}
	str = read_line(fd, buffer, str);
	free(buffer);
	if (!str)
		return (NULL);
	line = extract_line(str);
	str = save_remaining(str);
	return (line);
}
