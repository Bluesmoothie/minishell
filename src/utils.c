/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:18:50 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/14 23:44:46 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_str(char *str, int beg, int end)
{
	char	**result;
	char	tmp;
	int		i;
	int		size;

	size = end - beg;
	result = (char **)gmalloc_double(3 * sizeof(char *));
	result[0] = ft_strdup(str);
	result[1] = ft_substr(str, beg, size);
	result[2] = NULL;
	i = 0;
	while (i < beg)
		i++;
	while (result[0][i + size])
	{
		tmp = result[0][i + size];
		result[0][i] = tmp;
		i++;
	}
	ft_bzero(&result[0][i], size);
	return (result);
}
