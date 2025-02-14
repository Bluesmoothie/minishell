/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:13:45 by ygille            #+#    #+#             */
/*   Updated: 2025/02/14 23:52:05 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

/*
** Return a double pointer to the new allocated memory
** if malloc fail, call gclean then call exit_func 
** previsously selected with gset_exit
** with param and a personnalized message
** exit_func should call exit, if not gmalloc_double return NULL
*/
void	*gmalloc_double(size_t size)
{
	void	**ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		gclean();
		gcall_exit(EGMALLOC);
	}
	else
		double_garbage_col(GADDPTR, ptr);
	return (ptr);
}

/*
** Free a double pointer
** need to be ended by a NULL ptr
*/
void	gfree_double(void *ptr)
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
