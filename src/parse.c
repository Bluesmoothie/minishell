/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:38:14 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 17:39:23 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse the line
*/
void	parse_line(t_minishell *minishell, char *line)
{
	if (line == NULL)
		free_exit(minishell, NULL);
	add_history(line);
	unpipe(minishell, line);
}

/*
parse the argument either on a line either between two pipes
and executes
*/

void	treat_arguments(t_minishell *minishell, char *line, int fd)
{
	char	**args;

	args = miniparse(minishell, line);
	garbage_add_split(minishell, args);
	if (args[0] == NULL)
	{
		garbage_release_split(minishell, (void *)args);
		return ;
	}
	garbage_release(minishell, line);
	if (!builtin_functions(minishell, args, fd))
		try_launch(minishell, args);
	garbage_release_split(minishell, (void *)args);
	return ;
}

/*
** Check if the command is a builtin function
*/
t_bool	builtin_functions(t_minishell *minishell, char **args, int fd)
{
	if (ft_strcmp(args[0], "exit") == 0)
		free_exit(minishell, NULL);
	else if (ft_strcmp(args[0], "echo") == 0)
		minishell->last_return_value = func_echo(args, fd);
	else if (ft_strcmp(args[0], "cd") == 0)
		minishell->last_return_value = func_cd(minishell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		minishell->last_return_value = func_pwd(minishell, fd);
	else if (ft_strcmp(args[0], "export") == 0)
		minishell->last_return_value = func_export(minishell, args, fd);
	else if (ft_strcmp(args[0], "unset") == 0)
		minishell->last_return_value = func_unset(minishell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		minishell->last_return_value = func_env(minishell, fd);
	else
		return (FALSE);
	return (TRUE);
}

/*
** Try to launch the command from the PATH
*/
void	try_launch(t_minishell *minishell, char **args)
{
	char	*path;

	if (!ft_strncmp("/", args[0], 1))
		return (launch_bin(minishell, args[0], args));
	path = calc_bin_path(minishell, args);
	if (path != NULL)
	{
		launch_bin(minishell, path, args);
		garbage_release(minishell, path);
	}
	else
	{
		display_error(args[0], E_COMMANDNF, NULL);
		minishell->last_return_value = 127;
	}
}

/*
** Search the binary and return the complete path to it
** handling special ./ and ~/
*/
char	*calc_bin_path(t_minishell *minishell, char **args)
{
	char	**paths;
	char	*path;

	if (!ft_strncmp("./", args[0], 2))
		path = garbage_strfcat(minishell, minishell->pwd, &args[0][2], 0);
	else if (!ft_strncmp("~/", args[0], 2))
		path = garbage_strfcat(minishell, minishell->home, &args[0][1], 0);
	else
	{
		paths = garbage_split(minishell, get_env_value(minishell, "PATH"), ':');
		path = search_binary(minishell, paths, args[0]);
		garbage_release_split(minishell, paths);
	}
	return (path);
}
