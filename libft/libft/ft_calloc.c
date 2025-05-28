/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:19:51 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/10 16:25:57 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	x;
	void	*ptr;

	x = nmemb * size;
	if (size != 0 && ((x / size) != nmemb))
		return (NULL);
	ptr = malloc(x);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, x);
	return (ptr);
}
