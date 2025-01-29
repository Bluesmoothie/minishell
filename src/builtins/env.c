/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:29 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 19:27:13 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "ft_printf.h"

int	func_env(t_minishell *minishell)
{
	int		i;
	t_mlist	*lst;

	i = 0;
	while (minishell->envp[i] != NULL)
		ft_putendl_fd(minishell->envp[i++], 1);
	lst = minishell->extra_env;
	while (lst != NULL)
	{
		ft_putstr_fd(lst->name, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(lst->content, 1);
		lst = lst->next;
	}
	return (0);
}
