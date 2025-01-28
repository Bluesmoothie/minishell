/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:59:56 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:57:08 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*join;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = malloc(sizeof(char) * size);
	if (join == NULL)
		return (NULL);
	join[0] = '\0';
	ft_strlcat(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, size);
	return (join);
}
