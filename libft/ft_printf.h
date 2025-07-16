/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/16 17:47:41 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_put_char(int a);
int	ft_put_str(char *str);
int	ft_put_ptr(void *ptr);
int	ft_put_int(long int nb);
int	ft_put_unsign(unsigned int n);
int	ft_put_hex(unsigned int n, char format);

#endif
