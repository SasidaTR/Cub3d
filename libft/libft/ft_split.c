/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:09:32 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/08 17:45:29 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int	ft_word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	ft_free(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*ft_word_dup(char **result, const char *s, char c, int *j)
{
	char	*word;
	int		len;
	int		i;

	len = ft_word_len(s, c);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		ft_free(result, *j);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	result[*j] = word;
	(*j)++;
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!ft_word_dup(result, s + i, c, &j))
				return (NULL);
			i += ft_word_len(s + i, c);
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}
