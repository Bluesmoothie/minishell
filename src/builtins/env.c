/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:29 by ygille            #+#    #+#             */
/*   Updated: 2025/02/19 15:06:05 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(t_mlist *lst, int fd);

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

static void	print_export(t_mlist *lst, int fd)
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
