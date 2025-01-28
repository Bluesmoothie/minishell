/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:47 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:27:10 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
