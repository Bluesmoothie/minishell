/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:23:11 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 17:47:15 by ygille           ###   ########.fr       */
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
	node = garbage_lstnew(minishell, ptr);
	ft_lstadd_back(&minishell->garbage, node);
}

/*
** Free all pointer in the garbage list
*/
void	garbage_destroy(t_minishell *minishell)
{
	garbage_lstclear(minishell, &minishell->garbage);
	garbage_destroy_split(minishell, minishell->garbage_split);
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
	while (to_del->content != ptr && to_del != NULL)
	{
		prev = to_del;
		to_del = to_del->next;
	}
	if (to_del == NULL)
	{
		free (ptr);
		return ;
	}
	next = to_del->next;
	prev->next = next;
	garbage_lstdelone(to_del, minishell);
}

void	garbage_free_split(t_minishell *minishell, char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i])
		garbage_release(minishell, split[i++]);
	garbage_release(minishell, split);
}
