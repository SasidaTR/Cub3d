/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:34:30 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/26 18:09:14 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_chars;

	va_start(args, format);
	printed_chars = 0;
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			printed_chars += ft_parse_format(&format, args);
		}
		else
		{
			ft_putchar(*format);
			printed_chars++;
		}
		format++;
	}
	va_end(args);
	return (printed_chars);
}
