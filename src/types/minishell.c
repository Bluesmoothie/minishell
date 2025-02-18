/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:45:43 by ygille            #+#    #+#             */
/*   Updated: 2025/02/18 18:51:41 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_return_struct(t_return *ret);

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
	minishell->child_pid = 0;
	init_return_struct(&minishell->returns);
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

static void	init_return_struct(t_return *ret)
{
	ret->exit_stat = 0;
	ret->stopsig = 0;
	ret->termsig = 0;
	ret->exited = FALSE;
	ret->signaled = FALSE;
	ret->coredump = FALSE;
	ret->stopped = FALSE;
}
