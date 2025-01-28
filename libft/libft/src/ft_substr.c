/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:28 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:27:28 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (start > ft_strlen(s))
		size = 1;
	else
		size = ft_strlen(&s[start]) + 1;
	if (size > len)
		size = len + 1;
	sub = malloc (sizeof(char) * size);
	if (sub == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		sub[0] = '\0';
	else
		ft_strlcpy(sub, &s[start], size);
	return (sub);
}
