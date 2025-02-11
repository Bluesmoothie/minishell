/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:00:08 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 18:00:04 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

/*
** Malloc nmemb * size bytes then
** initialize each byte to 0
** return the allocated address or NULL on error
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	overflow;
	void	*array;

	overflow = nmemb * size;
	if (overflow / size == nmemb)
	{
		array = malloc (overflow);
		if (array != NULL)
			ft_bzero (array, overflow);
	}
	else
		array = NULL;
	return (array);
}
