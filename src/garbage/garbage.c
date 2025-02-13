/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:23:11 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 16:18:21 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Add a pointer to the garbage list
** not meant to be use outside of garbage collector itself
*/
void	garbage_add(t_minishell *minishell, void *ptr)
{
	t_list	*node;

	if (ptr == NULL)
		free_exit(minishell, E_MALLOC);
	node = ft_lstnew(ptr);
	if (node == NULL)
	{
		free (ptr);
		free_exit(minishell, E_MALLOC);
	}
	ft_lstadd_back(&minishell->garbage, node);
}

/*
** Free all pointer in the garbage list
*/
void	garbage_destroy(t_minishell *minishell)
{
	ft_lstclear(&minishell->garbage, &free);
	garbage_destroy_split(minishell->garbage);
}

/*
** Free a pointer and remove it from the garbage list
** you need to cast your pointer to (void *)
*/
void	garbage_release(t_minishell *minishell, void *ptr)
{
	t_list	*to_del;
	t_list	*prev;
	t_list	*next;

	to_del = minishell->garbage;
	while (to_del != ptr && to_del != NULL)
	{
		prev = to_del;
		to_del = to_del->next;
	}
	if (to_del == NULL)
		return ;
	next = to_del->next;
	prev->next = next;
	ft_lstdelone(to_del, &free);
}
