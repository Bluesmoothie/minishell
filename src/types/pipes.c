/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:39:09 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/11 17:16:43 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Free the memory of the list
*/
t_pipes	*pipeclear(t_pipes *lst)
{
	t_pipes	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
	return (NULL);
}

/*
** Create a new element of the list
*/
t_pipes	*pipecreate(char *content)
{
	t_pipes	*new;

	new = malloc(sizeof(t_pipes));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->next = NULL;
	return (new);
}

/*
** Add a new element at the beginning of the list
*/
void	pipeadd_back(t_pipes **lst, t_pipes *new)
{
	t_pipes	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = pipelast(*lst);
	last->next = new;
	return ;
}

/*
** Delete an element of the list
*/
void	pipedelone(t_pipes *lst)
{
	if (lst->content)
		free(lst->content);
	if (lst)
		free(lst);
}

/*
** Return the size of the list
*/
int	pipelstsize(t_mlist *lst)
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
