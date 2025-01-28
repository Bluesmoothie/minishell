/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:37:39 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:25:59 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		count;

	if (dest == NULL && src == NULL)
		return (dest);
	count = 0;
	while (count < n)
	{
		((char *)dest)[count] = ((const char *)src)[count];
		count++;
	}
	return (dest);
}
