/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:04 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:26:54 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(s) + 1;
	dup = malloc(sizeof(char) * size);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, size);
	return (dup);
}
