/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:45:43 by ygille            #+#    #+#             */
/*   Updated: 2025/02/16 13:40:13 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Init minishell struct
*/
void	init_struct(t_minishell *minishell, char **envp)
{
	minishell->home = getenv("HOME");
	minishell->user = getenv("USER");
	minishell->pwd = gman_add(getcwd(NULL, 0));
	minishell->last_return_value = 0;
	minishell->envp = envp;
	minishell->env = init_env(envp);
	minishell->prompt = calc_prompt(*minishell);
	minishell->garbage = NULL;
	minishell->garbage_split = NULL;
	minishell->child_pid = 0;
}

/*
** Free minishell struct
*/
void	free_struct(t_minishell *minishell)
{
	if (minishell->pwd)
	{
		gfree(minishell->pwd);
		minishell->pwd = NULL;
	}
	if (minishell->env)
		minishell->env = ft_mlstclear(minishell->env);
	if (minishell->prompt)
		gfree (minishell->prompt);
}

/*
** Update minishell struct
*/
void	update_infos(t_minishell *minishell)
{
	minishell->home = getenv("HOME");
	minishell->user = getenv("USER");
	if (minishell->pwd)
	{
		gfree(minishell->pwd);
		minishell->pwd = NULL;
	}
	minishell->pwd = gman_add(getcwd(NULL, 0));
	if (minishell->prompt)
	{
		gfree (minishell->prompt);
		minishell->prompt = NULL;
	}
	minishell->prompt = calc_prompt(*minishell);
}
