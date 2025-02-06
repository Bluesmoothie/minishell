/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:45:43 by ygille            #+#    #+#             */
/*   Updated: 2025/02/06 17:35:17 by ygille           ###   ########.fr       */
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
	minishell->env = init_env(envp);
}

void	free_struct(t_minishell *minishell)
{
	if (minishell->pwd)
	{
		free(minishell->pwd);
		minishell->pwd = NULL;
	}
	if (minishell->env)
		minishell->env = ft_mlstclear(minishell->env);
	if (minishell->prompt)
		free (minishell->prompt);
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
