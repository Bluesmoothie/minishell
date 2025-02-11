/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:14:21 by ygille            #+#    #+#             */
/*   Updated: 2025/02/11 17:14:54 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
