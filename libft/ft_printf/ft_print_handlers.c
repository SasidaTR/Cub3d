/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:18:22 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/20 17:22:23 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_format(const char **format, va_list args)
{
	int	printed_chars;

	printed_chars = 0;
	if (**format == 'c')
		printed_chars += ft_print_char(args);
	else if (**format == 's')
		printed_chars += ft_print_string(args);
	else if (**format == 'd' || **format == 'i')
		printed_chars += ft_print_number(args);
	else if (**format == 'x')
		printed_chars += ft_print_hex(args);
	else if (**format == 'X')
		printed_chars += ft_print_hex_upper(args);
	else if (**format == 'u')
		printed_chars += ft_print_unsigned(args);
	else if (**format == 'p')
		printed_chars += ft_print_pointer(args);
	else if (**format == '%')
		printed_chars += ft_print_percent();
	return (printed_chars);
}
