/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:46:31 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:31:31 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

/*
** Apply f on each node of lst
** return a new list with return values
** use del to delete the new list in an error occurs
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*modified_lst;
	t_list	*modified_new;
	void	*new_content;

	modified_lst = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			ft_lstclear(&modified_lst, del);
			return (NULL);
		}
		modified_new = ft_lstnew(new_content);
		if (!modified_new)
		{
			del(new_content);
			ft_lstclear(&modified_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&modified_lst, modified_new);
		lst = lst->next;
	}
	return (modified_lst);
}
