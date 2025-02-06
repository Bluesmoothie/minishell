/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:38:14 by ygille            #+#    #+#             */
/*   Updated: 2025/02/06 18:17:29 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse the line and execute the command
*/
void	parse_line(t_minishell *minishell, char *line)
{
	char	**args;

	if (line == NULL)
		free_exit(minishell, NULL, NULL);
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
		try_launch(minishell, args);
	free_split(&args);
	return ;
}

/*
** Check if the command is a builtin function
*/
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

/*
** Try to launch the command from the PATH
*/
void	try_launch(t_minishell *minishell, char **args)
{
	char	**paths;
	char	*path;

	if (!ft_strncmp("./", args[0], 2))
		return (local_launch(minishell, args));
	if (!ft_strncmp("/", args[0], 1))
		return (launch_bin(minishell, args[0], args));
	paths = ft_split(get_env_value(minishell, "PATH"), ':');
	if (paths == NULL)
		free_exit(minishell, args, E_MALLOCFAIL);
	path = search_binary(paths, args[0]);
	if (path != NULL)
	{
		launch_bin(minishell, path, args);
		free(path);
	}
	else
	{
		display_error(args[0], E_COMMANDNF, NULL);
		minishell->last_return_value = 127;
	}
	free_split(&paths);
}

void	local_launch(t_minishell *minishell, char **args)
{
	char	*path;

	path = ft_strfcat(minishell->pwd, &args[0][2], FALSE, FALSE);
	launch_bin(minishell, path, args);
	free(path);
}
