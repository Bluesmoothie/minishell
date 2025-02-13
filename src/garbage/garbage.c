/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:23:11 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 14:42:58 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Act like malloc but return only on sucess
** register the pointer in a garbage list
** /!\ you need to free this pointer with garbage_release /!\
** if malloc fail, automatically free all garbage and quit
*/
void	*garbage_malloc(t_minishell *minishell, size_t size)
{
	void	*ptr;
	t_list	node;

	ptr = malloc(size);
	if (ptr == NULL)
		free_exit(minishell, NULL, E_MALLOCFAIL);
	node = ft_lstnew(ptr);
	if (node == NULL)
		free_exit(minishell, NULL, E_MALLOCFAIL);
	ft_lstadd_back(&minishell->garbage, node);
	return (ptr);
}

/*
** Free all pointer in the garbage list
*/
void	garbage_destroy(t_minishell *minishell)
{
	ft_lstclear(minishell->garbage, &free);
}

/*
** Free a pointer and remove it from the garbage list
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
