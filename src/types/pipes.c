/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:39:09 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/16 14:52:04 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Create a new element of the list
*/
t_pipes	*pipecreate(char *content)
{
	t_pipes	*new;

	new = gmalloc(sizeof(t_pipes));
	new->content = content;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->next = NULL;
	new->issue = 0;
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
** Return the size of the list
*/
int	pipelstsize(t_pipes *lst)
{
	int		i;
	t_pipes	*tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
