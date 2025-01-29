/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:49:39 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 18:50:42 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*ft_mlstclear(t_mlist **lst)
{
	t_mlist	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	return (NULL);
}
