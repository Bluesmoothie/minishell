/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:28:57 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:56:54 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	count;

	count = 0;
	if (s == NULL)
		return (NULL);
	while (c > 127)
		c -= 128;
	while (s[count] != '\0' && s[count] != c)
		count++;
	if (s[count] == c)
		return ((char *)&s[count]);
	else
		return (NULL);
}
