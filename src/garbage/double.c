/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:13:45 by ygille            #+#    #+#             */
/*   Updated: 2025/02/14 19:28:57 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

/*
** Free a double pointer
** need to be ended by a NULL ptr
*/
void	gfree_double(void **ptr)
{
	gfree_double_helper(ptr);
	double_garbage_col(GRMPTR, ptr);
}

/*
** Intern usage only
*/
void	gfree_double_helper(void **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		garbage_col(GRMPTR, ptr[i]);
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
