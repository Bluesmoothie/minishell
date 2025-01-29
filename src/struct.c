/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:45:43 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 19:48:51 by ygille           ###   ########.fr       */
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

t_mlist	*init_env(char **envp)
{
	t_mlist	*env;
	char	*name;
	char	*content;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		name = extract_name(envp[i]);
		content = extract_content(envp[i]);
		env = ft_mlstadd_front(env, ft_mlstcreate(name, content));
		i++;
	}
	return (env);
}
