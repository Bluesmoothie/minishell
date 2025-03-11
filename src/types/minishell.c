/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:45:43 by ygille            #+#    #+#             */
/*   Updated: 2025/03/11 11:42:46 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_return_struct(t_return *ret);
static t_mlist	*init_minimal_env(void);

/*
** Init minishell struct
*/
void	init_struct(t_minishell *minishell, char **envp)
{
	minishell->env = init_env(envp);
	if (minishell->env != NULL)
	{
		minishell->home = getenv("HOME");
		minishell->user = getenv("USER");
	}
	else
	{
		minishell->home = NULL;
		minishell->user = NULL;
		minishell->env = init_minimal_env();
	}
	minishell->pwd = getcwd(NULL, 0);
	if (minishell->pwd != NULL)
		gman_add(minishell->pwd);
	minishell->last_return_value = 0;
	minishell->envp = envp;
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
	minishell->home = get_env_value(minishell, "HOME");
	minishell->user = get_env_value(minishell, "USER");
	if (minishell->pwd)
	{
		gfree(minishell->pwd);
		minishell->pwd = NULL;
	}
	minishell->pwd = getcwd(NULL, 0);
	if (minishell->pwd != NULL)
		gman_add(minishell->pwd);
	if (minishell->prompt)
	{
		gfree (minishell->prompt);
		minishell->prompt = NULL;
	}
	minishell->prompt = calc_prompt(*minishell);
	// update_pwdvar(minishell);
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

static t_mlist	*init_minimal_env(void)
{
	t_mlist	*env;
	char	*name;
	char	*content;

	env = NULL;
	name = gman_add(ft_strdup("OLDPWD"));
	content = NULL;
	env = ft_mlstadd_front(env, ft_mlstcreate(name, content));
	name = gman_add(ft_strdup("PWD"));
	content = getcwd(NULL, 0);
	if (content != NULL)
		gman_add(content);
	env = ft_mlstadd_front(env, ft_mlstcreate(name, content));
	name = gman_add(ft_strdup("SHLVL"));
	content = gman_add(ft_strdup("1"));
	env = ft_mlstadd_front(env, ft_mlstcreate(name, content));
	return (env);
}
