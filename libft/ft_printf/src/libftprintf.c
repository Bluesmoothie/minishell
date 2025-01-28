/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:42:13 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:08:36 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	handle_percent(const char *format, va_list *ap, int *i);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_putchar_fd(format[i], 1);
			j++;
			i++;
		}
		else
			j += handle_percent(format, &ap, &i);
	}
	va_end(ap);
	return (j);
}

static int	handle_percent(const char *format, va_list *ap, int *i)
{
	(*i) += 1;
	if (format[*i] == '%')
		return (print_percent(i));
	else if (format[*i] == 'c')
		return (print_char(i, ap));
	else if (format[*i] == 's')
		return (print_string(i, ap));
	else if (format[*i] == 'p')
		return (print_pointer(i, ap));
	else if (format[*i] == 'd')
		return (print_decimal(i, ap));
	else if (format[*i] == 'i')
		return (print_integer(i, ap));
	else if (format[*i] == 'u')
		return (print_unsigned_decimal(i, ap));
	else if (format[*i] == 'x' || format[*i] == 'X')
		return (print_hex(i, ap, format[*i]));
	return (0);
}

// #include <stdio.h>
// #include <limits.h>
// int	main(void)
// {
// 	int	a;
// 	int	b;

// 	a = printf(" %p %p \n", (void *)LONG_MIN, (void *)LONG_MAX);
// 	b = ft_printf(" %p %p \n", (void *)LONG_MIN, (void *)LONG_MAX);
// 	printf("return    printf = %d\nreturn ft_printf = %d\n", a, b);
// 	return (0);
// }
