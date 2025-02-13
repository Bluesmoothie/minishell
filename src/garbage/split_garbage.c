/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:34:55 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 16:23:57 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** /!\ you need to free this pointer with garbage_release_split /!\
*/
char	**garbage_split(t_minishell *minishell, const char *s, char c)
{
	char	**result;

	result = ft_split(s, c);
	garbage_add_split(minishell, (void *)result);
	return (result);
}

/*
** Add a pointer to the garbage split list
** not meant to be use outside of garbage collector itself
*/
void	garbage_add_split(t_minishell *minishell, void *ptr)
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
	ft_lstadd_back(&minishell->garbage_split, node);
}

/*
** Free a split pointer and remove it from the garbage list
** you need to cast your pointer to (void *)
*/
void	garbage_release_split(t_minishell *minishell, void *ptr)
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
	ft_lstdelone(to_del, &garbage_free_split);
}

void	garbage_destroy_split(t_list *list)
{
	ft_lstclear(&list, &garbage_free_split);
}

void	garbage_free_split(void *list)
{
	char	**split;
	t_list	*lst;

	lst = (t_list *)list;
	split = (char **)lst->content;
	free_split(&split);
}
