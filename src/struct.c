/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:45:43 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 19:04:59 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_minishell *minishell, char **envp)
{
	minishell->home = getenv("HOME");
	minishell->user = getenv("USER");
	minishell->pwd = getcwd(NULL, 0);
	minishell->last_return_value = 0;
	minishell->envp = envp;
	minishell->extra_env = NULL;
}

void	free_struct(t_minishell *minishell)
{
	if (minishell->pwd)
	{
		free(minishell->pwd);
		minishell->pwd = NULL;
	}
	if (minishell->extra_env)
		minishell->extra_env = ft_mlstclear(&minishell->extra_env);
}

void	update_infos(t_minishell *minishell)
{
	minishell->home = getenv("HOME");
	minishell->user = getenv("USER");
	if (minishell->pwd)
	{
		free(minishell->pwd);
		minishell->pwd = NULL;
	}
	minishell->pwd = getcwd(NULL, 0);
}
