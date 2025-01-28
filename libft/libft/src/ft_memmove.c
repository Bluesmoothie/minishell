/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:36:03 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:26:01 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == NULL && src == NULL)
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
