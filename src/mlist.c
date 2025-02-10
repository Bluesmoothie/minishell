/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:49:39 by ygille            #+#    #+#             */
/*   Updated: 2025/02/10 14:59:36 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Free the memory of the list
*/
t_mlist	*ft_mlstclear(t_mlist *lst)
{
	t_mlist	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		if (lst->name)
			free(lst->name);
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = tmp;
	}
	return (NULL);
}

/*
** Create a new element of the list
*/
t_mlist	*ft_mlstcreate(char *name, char *content)
{
	t_mlist	*new;

	new = malloc(sizeof(t_mlist));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
}

/*
** Add a new element at the beginning of the list
*/
t_mlist	*ft_mlstadd_front(t_mlist *lst, t_mlist *new)
{
	if (new == NULL)
		return (NULL);
	new->next = lst;
	lst = new;
	return (lst);
}

/*
** Delete an element of the list
*/
void	ft_mlstdelone(t_mlist *lst)
{
	if (lst->name)
		free(lst->name);
	if (lst->content)
		free(lst->content);
	if (lst)
		free(lst);
}

/*
** Return the size of the list
*/
int	ft_mlstsize(t_mlist *lst)
{
	int		i;
	t_mlist	*tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
