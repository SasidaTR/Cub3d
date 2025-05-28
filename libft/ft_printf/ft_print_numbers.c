/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:36:02 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/20 17:17:47 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_number(va_list args)
{
	int	n;
	int	len;
	int	temp;

	n = va_arg(args, int);
	len = 0;
	temp = n;
	if (n == INT_MIN)
	{
		ft_putnbr_generic(n);
		return (11);
	}
	if (n <= 0)
		len++;
	while (temp)
	{
		temp /= 10;
		len++;
	}
	ft_putnbr_generic(n);
	return (len);
}

int	ft_print_unsigned(va_list args)
{
	unsigned int	n;
	int				len;
	unsigned int	temp;

	n = va_arg(args, int);
	len = 0;
	temp = n;
	if (n == 0)
		return (write(1, "0", 1));
	while (temp)
	{
		temp /= 10;
		len++;
	}
	ft_putnbr_unsigned(n);
	return (len);
}
