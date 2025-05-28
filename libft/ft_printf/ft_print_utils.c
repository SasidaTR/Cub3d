/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:18:56 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/20 17:55:19 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_putnbr_generic(long long n)
{
	if (n < 0)
	{
		if (n == LLONG_MIN)
		{
			ft_putstr("-9223372036854775808");
			return ;
		}
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		ft_putnbr_generic(n / 10);
	ft_putchar(n % 10 + '0');
}

void	ft_putnbr_unsigned(unsigned int n)
{
	if (n > 9)
		ft_putnbr_unsigned(n / 10);
	ft_putchar(n % 10 + '0');
}

void	ft_putnbr_base(unsigned long long n, char *base)
{
	unsigned long long	base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	if (n >= base_len)
		ft_putnbr_base(n / base_len, base);
	ft_putchar(base[n % base_len]);
}
