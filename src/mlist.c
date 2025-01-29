/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:49:39 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 19:36:54 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*ft_mlstclear(t_mlist *lst)
{
	t_mlist	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->name);
		free(lst->content);
		free(lst);
		lst = tmp;
	}
	return (NULL);
}

t_mlist	*ft_mlstcreate(char *name, char *content)
{
	t_mlist	*new;

	new = malloc(sizeof(t_mlist));
	if (new == NULL)
		return (NULL);
	new->name = ft_strdup(name);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}

t_mlist	*ft_mlstadd_front(t_mlist *lst, t_mlist *new)
{
	if (new == NULL)
		return (NULL);
	new->next = lst;
	lst = new;
	return (lst);
}

void	ft_mlstdelone(t_mlist *lst)
{
	if (lst->name)
		free(lst->name);
	if (lst->content)
		free(lst->content);
	if (lst)
		free(lst);
}
