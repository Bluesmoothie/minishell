/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:47:16 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:32:38 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/*
** Return the last occurence of c in s
** NULL if not found
*/
char	*ft_strrchr(const char *s, int c)
{
	size_t	count;

	count = ft_strlen(s);
	while (c > 127)
		c -= 128;
	while (count != 0 && s[count] != c)
		count--;
	if (s[count] == c)
		return ((char *)&s[count]);
	else
		return (NULL);
}
