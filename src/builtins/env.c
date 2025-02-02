/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:29 by ygille            #+#    #+#             */
/*   Updated: 2025/02/02 19:37:26 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the env command, display the environment variables
*/
int	func_env(t_minishell *minishell)
{
	t_mlist	*lst;

	lst = minishell->env;
	while (lst != NULL)
	{
		ft_putstr_fd(lst->name, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(lst->content, 1);
		lst = lst->next;
	}
	return (0);
}
