/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:26:52 by ygille            #+#    #+#             */
/*   Updated: 2025/02/11 14:27:09 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/*
** Like strcat but can choose if a string needs to be freed
*/
char	*ft_strfcat(char *s1, char *s2, t_bool fs1, t_bool fs2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1 != NULL)
		while (s1[j])
			str[i++] = s1[j++];
	j = 0;
	if (s2 != NULL)
		while (s2[j])
			str[i++] = s2[j++];
	str[i] = '\0';
	if (fs1 && s1 != NULL)
		free(s1);
	if (fs2 && s2 != NULL)
		free(s2);
	return (str);
}
