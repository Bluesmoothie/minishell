/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:16:27 by ygille            #+#    #+#             */
/*   Updated: 2025/02/18 13:30:54 by ygille           ###   ########.fr       */
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
	gman_add(ptr);
	return (ptr);
}

/*
** Manually add a ptr to the ptr list
** verifying if he his not NULL
** otherwise calls the exit function
** return the ptr
*/
void	*gman_add(void *ptr)
{
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
	if (ptr == NULL)
		return ;
	garbage_col(GRMPTR, ptr);
	free(ptr);
}

/*
** Free all memory previously allocated with gmalloc and gmalloc_double
** that is not allready freed with gfree
*/
void	gclean(void)
{
	double_garbage_col(GCLEANALL, NULL);
	garbage_col(GCLEANALL, NULL);
}
