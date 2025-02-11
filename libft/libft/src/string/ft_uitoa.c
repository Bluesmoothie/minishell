/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:44:22 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 20:02:47 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

static char	*alloc_reverse(char *input, int i);

char	*ft_uitoa(unsigned int n)
{
	char	res[12];
	int		i;

	i = 0;
	if (n == 0)
	{
		res[i] = '0';
		i++;
	}
	while (n)
	{
		res[i++] = n % 10 + '0';
		n /= 10;
	}
	return (alloc_reverse(res, i - 1));
}

static char	*alloc_reverse(char *input, int i)
{
	int		j;
	char	*res;

	j = 0;
	res = malloc (sizeof(char) * i + 2);
	if (res == NULL)
		return (res);
	while (i >= 0)
		res[j++] = input[i--];
	res[j] = '\0';
	return (res);
}
