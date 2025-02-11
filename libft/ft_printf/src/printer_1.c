/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:49:38 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 19:54:02 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_percent(int *i)
{
	(*i) += 1;
	ft_putchar_fd('%', 1);
	return (1);
}

int	print_char(int *i, va_list *ap)
{
	(*i) += 1;
	ft_putchar_fd(va_arg(*ap, int), 1);
	return (1);
}

int	print_string(int *i, va_list *ap)
{
	char	*s;

	(*i) += 1;
	s = va_arg(*ap, char *);
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	else
	{
		ft_putstr_fd(s, 1);
		return (ft_strlen(s));
	}
}

int	print_pointer(int *i, va_list *ap)
{
	int					j;
	unsigned long long	val;

	(*i) += 1;
	val = va_arg(*ap, unsigned long long);
	j = 0;
	if (val == 0)
	{
		j += 5;
		ft_putstr_fd("(nil)", 1);
	}
	else
	{
		j += 2;
		ft_putstr_fd("0x", 1);
		hex(val, LOW, &j);
	}
	return (j);
}

int	print_decimal(int *i, va_list *ap)
{
	char	*num;
	int		size;

	(*i) += 1;
	num = ft_itoa(va_arg(*ap, int));
	ft_putstr_fd(num, 1);
	size = ft_strlen(num);
	free(num);
	return (size);
}
