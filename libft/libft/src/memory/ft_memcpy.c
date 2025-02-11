/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:37:39 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 18:00:47 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

/*
** Copy n bytes from src to dest
** return dest
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		count;

	if (dest == NULL || src == NULL)
		return (dest);
	count = 0;
	while (count < n)
	{
		((char *)dest)[count] = ((const char *)src)[count];
		count++;
	}
	return (dest);
}
