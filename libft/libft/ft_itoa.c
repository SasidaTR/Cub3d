/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:01:08 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/04 18:50:42 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int		count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;
	int		sign;

	sign = 1;
	count = ft_count(n);
	if (n < 0)
		sign = -1;
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	str[count] = '\0';
	count--;
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[count] = (n % 10) * sign + '0';
		n = n / 10;
		count--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
