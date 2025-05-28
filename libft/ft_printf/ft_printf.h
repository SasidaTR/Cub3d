/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:59:08 by douzgane          #+#    #+#             */
/*   Updated: 2024/06/20 17:33:25 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_printf(const char *format, ...);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr_generic(long long n);
void	ft_putnbr_base(unsigned long long n, char *base);
void	ft_putnbr_unsigned(unsigned int n);
int		ft_parse_format(const char **format, va_list args);
int		ft_print_char(va_list args);
int		ft_print_string(va_list args);
int		ft_print_number(va_list args);
int		ft_print_hex(va_list args);
int		ft_print_hex_upper(va_list args);
int		ft_print_unsigned(va_list args);
int		ft_print_pointer(va_list args);
int		ft_print_percent(void);

#endif
