/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:03:41 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:32:36 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/*
** Search in up to len bytes of big for little
** return the pointer to the start of little in big
** NULL if not found
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] != '\0')
			j++;
		if (little[j] == '\0' && i + j - 1 < len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
