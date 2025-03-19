/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:16 by ygille            #+#    #+#             */
/*   Updated: 2025/03/19 12:21:53 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the unset command, remove an environment variable
*/
int	func_unset(t_minishell *minishell, char **args)
{
	t_mlist	*prev;
	t_mlist	*del;
	t_mlist	*next;

	if (args[1] == NULL)
		return (0);
	prev = NULL;
	del = minishell->env;
	while (del != NULL)
	{
		next = del->next;
		if (ft_strcmp(del->name, args[1]) == 0)
		{
			if (prev == NULL)
				minishell->env = next;
			else
				prev->next = next;
			ft_mlstdelone(del);
			return (suit(&func_unset, minishell, args));
		}
		prev = del;
		del = next;
	}
	return (suit(&func_unset, minishell, args));
}
