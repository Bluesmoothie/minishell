/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:01:28 by ygille            #+#    #+#             */
/*   Updated: 2025/02/14 13:29:46 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

void	garbage_col(int op_code, void *ptr)
{
	static void		*glist[GARBAGE_SIZE];
	static size_t	act_gsize = 0;

	if (ptr == NULL)
		return ;
	if (op_code == ADDPTR)
		garbage_add(glist, &act_gsize, ptr);
	else if (op_code == RMPTR)
		garbage_remove(glist, &act_gsize, ptr);
}

void	garbage_add(void *glist[], size_t *gsize, void *ptr)
{
	if (*gsize == GARBAGE_SIZE)
		return (garbage_error(E_GFULL));
	glist[*gsize] = ptr;
	(*gsize)++;
}

void	garbage_remove(void *glist[], size_t *gsize, void *ptr)
{
	size_t	i;

	if (*gsize == 0)
		return ;
	i = 0;
	while (i < *gsize && glist[i] != ptr)
		i++;
	if (i == *gsize)
#if GARBAGE_WARN_NF
		return (garbage_error(E_GNF);
#else
		return ;
#endif
	glist[i] = NULL;
	if (i < *gsize - 1)
	{
		glist[i] = glist[*gsize - 1];
		glist[*gsize - 1] = NULL;
	}
	(*gsize)--;
}

void	garbage_error(char *message)
{
	ft_putendl_fd(message, STDERR_FILENO);
}
