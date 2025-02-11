/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:54:24 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:32:33 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/*
** Compare the first n bytes of s1 and s2
** return 0 if equals
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (0);
	while (s1[count] != '\0' && s1[count] == s2[count] && count < n - 1)
		count++;
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}
