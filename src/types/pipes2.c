/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:14:21 by ygille            #+#    #+#             */
/*   Updated: 2025/04/11 10:47:20 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipedelone(t_pipes *lst);

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

void	pipedelone(t_pipes *lst)
{
	if (!lst)
		return ;
	if (lst)
		gfree(lst);
}
