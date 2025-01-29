/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:16 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 19:36:09 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	func_unset(t_minishell *minishell, char **args)
{
	t_mlist	*prev;
	t_mlist	*del;
	t_mlist	*next;

	if (args[1] == NULL)
		return (0);
	prev = NULL;
	del = minishell->extra_env;
	while (del != NULL)
	{
		next = del->next;
		if (ft_strcmp(del->name, args[1]) == 0)
		{
			if (prev == NULL)
				minishell->extra_env = next;
			else
				prev->next = next;
			ft_mlstdelone(del);
			return (0);
		}
		prev = del;
		del = next;
	}
	return (0);
}
