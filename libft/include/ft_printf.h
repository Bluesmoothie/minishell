/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:36:59 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 14:02:50 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define LOW_BASE_HEX	"0123456789abcdef"
# define UP_BASE_HEX	"0123456789ABCDEF"
# define UP				'X'
# define LOW			'x'

# include <libft.h>
# include <stdarg.h>

//libftprintf.c
int		ft_printf(const char *format, ...);

//printer_1.c
int		print_percent(int *i);
int		print_char(int *i, va_list *ap);
int		print_string(int *i, va_list *ap);
int		print_pointer(int *i, va_list *ap);
int		print_decimal(int *i, va_list *ap);

//printer_2.c
int		print_integer(int *i, va_list *ap);
int		print_unsigned_decimal(int *i, va_list *ap);
int		print_hex(int *i, va_list *ap, char format);

//hex.c
void	hex(unsigned long long val, char format, int *i);

//ft_uitoa.c
char	*ft_uitoa(unsigned int n);

#endif