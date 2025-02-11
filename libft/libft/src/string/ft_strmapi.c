/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:47 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:32:31 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/*
** Apply f on each character of s
** return a new string with return values
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	size_t	i;
	char	*res;

	size = ft_strlen(s);
	res = malloc (sizeof(char) * size + 1);
	if (res == NULL)
		return (res);
	i = 0;
	while (i < size)
	{
		res[i] = f((unsigned int)i, s[i]);
		i++;
	}
	res [i] = '\0';
	return (res);
}
