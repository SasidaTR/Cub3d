/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:03:16 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/20 19:23:00 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_pointer(unsigned long long n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		ft_putnbr_pointer(n / 16);
	ft_putchar(base[n % 16]);
}

int	ft_print_pointer(va_list args)
{
	unsigned long long	ptr;
	int					len;

	ptr = (unsigned long long)va_arg(args, void *);
	len = 3;
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	len = 2;
	ft_putnbr_pointer(ptr);
	while (ptr)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}
