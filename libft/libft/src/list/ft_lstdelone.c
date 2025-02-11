/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:22:10 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:54:18 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

/*
** Delte one node at lst using del
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst != NULL)
	{
		del (lst->content);
		free(lst);
	}
}
