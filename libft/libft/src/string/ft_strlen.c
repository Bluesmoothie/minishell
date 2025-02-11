/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:24:26 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:32:29 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/*
** Return the size of s
*/
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}
