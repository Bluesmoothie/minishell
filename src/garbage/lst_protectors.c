/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_protector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:28:37 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 17:45:12 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	garbage_lstclear(t_minishell *minishell, t_list **lst)
{
	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		garbage_lstdelone(*lst, minishell);
		*lst = tmp;
	}
}
void	garbage_lstdelone(t_list *lst, t_minishell *minishell)
{
	if (lst != NULL)
	{
		garbage_release(minishell, lst->content);
		garbage_release(minishell, lst);
	}
}

t_list	*garbage_lstnew(t_minishell *minishell, void *content)
{
	t_list	*new;

	new = garbage_malloc (minishell, sizeof(t_list));
	new->content = content;
	new->next = NULL;
	return (new);
}
