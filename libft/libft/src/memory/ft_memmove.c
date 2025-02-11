/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:36:03 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 17:08:43 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

/*
** Copy n bytes from src to dest
** src and dest can overlap each other
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == NULL || src == NULL)
		return (dest);
	if (dest < src)
		ft_memcpy (dest, src, n);
	else
	{
		while (n--)
			((char *)dest)[n] = ((const char *)src)[n];
	}
	return (dest);
}
