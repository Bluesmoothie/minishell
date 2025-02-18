/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:29 by ygille            #+#    #+#             */
/*   Updated: 2025/02/18 16:23:12 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_mlist *lst, int fd);

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
			print_export(lst, fd);
		else if (lst->content)
		{
			ft_putstr_fd(lst->name, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(lst->content, fd);
		}
		lst = lst->next;
	}
	return (0);
}

void	print_export(t_mlist *lst, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(lst->name, fd);
	if (lst->content)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(lst->content, fd);
		ft_putendl_fd("\"", fd);
	}
	else
		ft_putstr_fd("\n", fd);
}
