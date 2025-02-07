/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:29 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 13:07:43 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the env command, display the environment variables
*/
int	func_env(t_minishell *minishell, int fd)
{
	t_mlist	*lst;

	lst = minishell->env;
	while (lst != NULL)
	{
		ft_putstr_fd(lst->name, fd);
		ft_putstr_fd("=", fd);
		ft_putendl_fd(lst->content, fd);
		lst = lst->next;
	}
	return (0);
}
