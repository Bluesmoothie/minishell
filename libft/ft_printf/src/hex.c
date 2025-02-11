/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:11:31 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 19:53:55 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hex(unsigned long long val, char format, int *i)
{
	if (val / 16)
		hex(val / 16, format, i);
	if (format == UP)
		ft_putchar_fd(UP_BASE_HEX[val % 16], 1);
	else
		ft_putchar_fd(LOW_BASE_HEX[val % 16], 1);
	(*i) += 1;
	return ;
}
