/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:38:14 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 15:08:49 by ygille           ###   ########.fr       */
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
		func_echo(minishell, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		func_cd(minishell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		func_pwd(minishell);
	else if (ft_strcmp(args[0], "export") == 0)
		func_export(minishell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		func_unset(minishell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		func_env(minishell);
	else
		return (FALSE);
	return (TRUE);
}

void	try_launch(char **args)
{
	display_error(args[0], E_COMMANDNF, NULL);
}
