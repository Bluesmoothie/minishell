/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:13:41 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 21:17:13 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

void	*ft_smalloc(int	nmemb, int size, void *param, void (free_exit)(void *param)(char *message))
{
	size_t	overflow;
	void	*array;

	overflow = nmemb * size;
	array = NULL;
	if (overflow / size == nmemb)
		array = malloc (overflow);
	return (array);
}
