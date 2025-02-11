/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:17:23 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:31:06 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"

/*
** If c is a uppercase character
** return it's corresponding lowercase
*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
