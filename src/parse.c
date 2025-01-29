/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:38:14 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 19:19:57 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(t_minishell *minishell, char *line)
{
	char	**args;

	if (line == NULL)
		return ;
	args = ft_split(line, ' ');
	if (args == NULL)
		free_exit(minishell, args, E_SPLITFAIL);
	if (args[0] == NULL)
	{
		free_split(&args);
		return ;
	}
	add_history(line);
	free(line);
	search_for_env(minishell, &args);
	if (!builtin_functions(minishell, args))
		try_launch(args);
	free_split(&args);
	return ;
}

t_bool	builtin_functions(t_minishell *minishell, char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
		free_exit(minishell, args, NULL);
	else if (ft_strcmp(args[0], "echo") == 0)
		minishell->last_return_value = func_echo(minishell, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		minishell->last_return_value = func_cd(minishell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		minishell->last_return_value = func_pwd(minishell);
	else if (ft_strcmp(args[0], "export") == 0)
		minishell->last_return_value = func_export(minishell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		minishell->last_return_value = func_unset(minishell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		minishell->last_return_value = func_env(minishell);
	else
		return (FALSE);
	return (TRUE);
}

void	try_launch(char **args)
{
	display_error(args[0], E_COMMANDNF, NULL);
}

void	search_for_env(t_minishell *minishell, char ***args)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*args)[i] != NULL)
	{
		if ((*args)[i][0] == '$' && (*args)[i][1] != '\0')
		{
			tmp = (*args)[i];
			(*args)[i] = get_env_value(minishell, &tmp[1]);
			free(tmp);
		}
		i++;
	}
}

char	*get_env_value(t_minishell *minishell, char *arg)
{
	t_mlist	*mlist;

	if (ft_strcmp(arg, "?") == 0)
		return (ft_itoa(minishell->last_return_value));
	mlist = minishell->extra_env;
	while (mlist != NULL)
	{
		if (ft_strcmp(mlist->name, arg) == 0)
			return (ft_strdup(mlist->content));
		mlist = mlist->next;
	}
	return (ft_strdup(getenv(arg)));
}
