/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:29 by ygille            #+#    #+#             */
/*   Updated: 2025/02/17 15:50:09 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the env command, display the environment variables
*/
int	func_env(t_minishell *minishell, int fd, t_bool export)
{
	t_mlist	*lst;

	lst = minishell->env;
	while (lst != NULL)
	{
		if (export)
			ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(lst->name, fd);
		ft_putstr_fd("=", fd);
		if (export)
		{	
			ft_putstr_fd("\"", fd);
			ft_putstr_fd(lst->content, fd);
			ft_putendl_fd("\"", fd);
		}
		else
			ft_putendl_fd(lst->content, fd);
		lst = lst->next;
	}
	return (0);
}
