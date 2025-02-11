/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:54:03 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 21:14:05 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/*
** Free a split array
*/
void	ft_free_split(char **split)
{
	size_t	i;

	if (split)
	{
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
	}
}
