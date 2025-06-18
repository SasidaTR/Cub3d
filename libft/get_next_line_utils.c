/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:59:50 by douzgane          #+#    #+#             */
/*   Updated: 2025/06/18 16:52:14 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

static char	*init_empty_str(void)
{
	char	*s;

	s = malloc(1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

static void	copy_strings(char *str, char *s1, char *s2, int *i)
{
	int	j;

	j = 0;
	while (s1[*i])
	{
		str[*i] = s1[*i];
		(*i)++;
	}
	while (s2[j])
	{
		str[*i] = s2[j];
		(*i)++;
		j++;
	}
	str[*i] = '\0';
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;

	if (!s1)
	{
		s1 = init_empty_str();
		if (!s1)
			return (NULL);
	}
	str = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	copy_strings(str, s1, s2, &i);
	free(s1);
	return (str);
}
