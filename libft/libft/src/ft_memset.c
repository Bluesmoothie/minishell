/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:29:44 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:26:04 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		((char *)s)[count] = c;
		count++;
	}
	return (s);
}
