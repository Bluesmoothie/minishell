/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:29 by ygille            #+#    #+#             */
/*   Updated: 2025/03/18 18:18:29 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(t_mlist *lst);

/*
** Like the env command, display the environment variables
*/
int	func_env(t_minishell *minishell, t_bool export)
{
	t_mlist	*lst;

	lst = minishell->env;
	while (lst != NULL)
	{
		if (export)
			print_export(lst);
		else if (lst->content)
		{
			ft_putstr_fd(lst->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(lst->content, STDOUT_FILENO);
		}
		lst = lst->next;
	}
	return (0);
}

/*
** When export is called without arguments
** print the environnement
*/
static void	print_export(t_mlist *lst)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(lst->name, STDOUT_FILENO);
	if (lst->content)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(lst->content, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
}
