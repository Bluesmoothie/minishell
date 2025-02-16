/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:14:21 by ygille            #+#    #+#             */
/*   Updated: 2025/02/16 14:52:46 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipedeltwo(t_pipes *lst);
static void	pipedelone(t_pipes *lst);

/*
** Return a pointe to the last node of lst
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
	gfree(lst);
}


void	pipeclear2(t_pipes **lst)
{
	t_pipes	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		pipedeltwo(*lst);
		*lst = tmp;
	}
	gfree(lst);
}


/*
** Delete an element of the list
*/
static void	pipedelone(t_pipes *lst)
{
	if (!lst)
		return ;
	if (lst->content)
		gfree(lst->content);
	if (lst)
		gfree(lst);
}


static void	pipedeltwo(t_pipes *lst)
{
	if (!lst)
		return ;
	if (lst)
		gfree(lst);
}
