/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:14:21 by ygille            #+#    #+#             */
/*   Updated: 2025/02/17 19:58:52 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipedelone(t_pipes *lst);

/*
** Return a pointer to the last node of lst
*/
t_pipes	*pipelast(t_pipes *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	pipeclear(t_pipes **lst)
{
	t_pipes	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		pipedelone(*lst);
		*lst = tmp;
	}
	lst = NULL;
}

static void	pipedelone(t_pipes *lst)
{
	if (!lst)
		return ;
	if (lst)
		gfree(lst);
}
