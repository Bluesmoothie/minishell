/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:22:26 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 13:25:45 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc (sizeof(t_list));
	if (new == NULL)
		return (new);
	new->content = content;
	new->next = NULL;
	return (new);
}
