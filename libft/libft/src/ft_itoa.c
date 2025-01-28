/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:24:54 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:25:22 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*alloc_reverse(char *input, int sign, int i);

char	*ft_itoa(int n)
{
	char	res[12];
	int		sign;
	long	num;
	int		i;

	sign = 1;
	num = (long)n;
	i = 0;
	if (num < 0)
	{
		num *= -1;
		sign *= -1;
	}
	if (num == 0)
	{
		res[i] = '0';
		i++;
	}
	while (num)
	{
		res[i++] = num % 10 + '0';
		num /= 10;
	}
	return (alloc_reverse(res, sign, i - 1));
}

static char	*alloc_reverse(char *input, int sign, int i)
{
	int		j;
	char	*res;

	j = 0;
	if (sign == 1)
	{
		res = malloc (sizeof(char) * i + 2);
		if (res == NULL)
			return (res);
	}
	else
	{
		res = malloc (sizeof(char) * i + 3);
		if (res == NULL)
			return (res);
		res[j] = '-';
		j++;
	}
	while (i >= 0)
		res[j++] = input[i--];
	res[j] = '\0';
	return (res);
}
