/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:02:13 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:54:44 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

/*
** Return the pointer to the last node of lst
*/
t_list	*ft_lstlast(t_list *lst)
{
	if (lst != NULL)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}
