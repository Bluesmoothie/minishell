/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:43:52 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:57:18 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (src == NULL && size == 1)
	{
		dst[0] = '\0';
		return (1);
	}
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	if (i == size)
		return (i + ft_strlen(src));
	while (src[j] && i + j < size - 1 && src != NULL)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
