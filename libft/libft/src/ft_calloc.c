/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:00:08 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:27:45 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	long	overflow;

	overflow = nmemb * size;
	if (overflow > INT_MAX)
		return (NULL);
	array = malloc (overflow);
	if (array == NULL)
		return (NULL);
	ft_bzero (array, overflow);
	return (array);
}
