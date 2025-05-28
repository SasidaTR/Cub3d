/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:43:41 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/20 17:23:25 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(va_list args)
{
	unsigned int	n;
	char			*base;
	int				len;
	unsigned int	temp;

	n = va_arg(args, unsigned int);
	base = "0123456789abcdef";
	len = 0;
	temp = n;
	if (n == 0)
		return (write(1, "0", 1));
	while (temp)
	{
		temp /= 16;
		len++;
	}
	ft_putnbr_base(n, base);
	return (len);
}

int	ft_print_hex_upper(va_list args)
{
	unsigned int	n;
	char			*base;
	int				len;
	unsigned int	temp;

	n = va_arg(args, unsigned int);
	base = "0123456789ABCDEF";
	len = 0;
	temp = n;
	if (n == 0)
		return (write(1, "0", 1));
	while (temp)
	{
		temp /= 16;
		len++;
	}
	ft_putnbr_base(n, base);
	return (len);
}
