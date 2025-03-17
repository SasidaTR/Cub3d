#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line.h"

int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);

#endif