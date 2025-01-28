/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:34:33 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:08:42 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	print_integer(int *i, va_list *ap)
{
	return (print_decimal(i, ap));
}

int	print_unsigned_decimal(int *i, va_list *ap)
{
	char	*num;
	int		size;

	(*i) += 1;
	num = ft_uitoa(va_arg(*ap, unsigned int));
	ft_putstr_fd(num, 1);
	size = ft_strlen(num);
	free(num);
	return (size);
}

int	print_hex(int *i, va_list *ap, char format)
{
	int	j;

	(*i) += 1;
	j = 0;
	hex(va_arg(*ap, unsigned int), format, &j);
	return (j);
}
