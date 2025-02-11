/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:23:54 by ygille            #+#    #+#             */
/*   Updated: 2025/02/11 16:57:52 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Add a new element at the end of the list
*/
t_mlist	*ft_mlstadd_back(t_mlist *lst, t_mlist *new)
{
	t_mlist	*last;

	if (new == NULL)
		return (NULL);
	if (lst == NULL)
		return (new);
	last = ft_mlstlast(lst);
	last->next = new;
	return (lst);
}

/*
** Return the last element of a list
*/
t_mlist	*ft_mlstlast(t_mlist *lst)
{
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/*
** Search for find in all nodes of lst
** return the node if found or NULL if not
*/
t_mlist	*ft_mlstsearch(t_mlist *lst, char *find)
{
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, find) == 0)
			break ;
		lst = lst->next;
	}
	return (lst);
}
