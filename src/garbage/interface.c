/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:16:27 by ygille            #+#    #+#             */
/*   Updated: 2025/02/14 23:41:37 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

/*
** Return a pointer to the new allocated memory
** if malloc fail, call gclean then call exit_func 
** previsously selected with gset_exit
** with param and a personnalized message
** exit_func should call exit, if not gmalloc return NULL
*/
void	*gmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		gclean();
		gcall_exit(EGMALLOC);
	}
	else
		garbage_col(GADDPTR, ptr);
	return (ptr);
}

/*
** Free memory allocated with gmalloc
*/
void	gfree(void *ptr)
{
	garbage_col(GRMPTR, ptr);
	free(ptr);
}

/*
** Free all memory previously allocated with gmalloc and gmalloc_double
** that is not allready freed with gfree
*/
void	gclean(void)
{
	garbage_col(GCLEANALL, NULL);
	double_garbage_col(GCLEANALL, NULL);
}
