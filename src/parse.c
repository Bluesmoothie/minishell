/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:38:14 by ygille            #+#    #+#             */
/*   Updated: 2025/03/10 16:32:53 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse the line
*/
void	parse_line(t_minishell *minishell, char *line)
{
	if (line == NULL)
		gcall_exit(NULL);
	if (line[0] != '\0')
		add_history(line);
	unpipe(minishell, line, quotes_verif(line));
}

/*
parse the argument either on a line either between two pipes
and executes
*/

void	treat_arguments(t_minishell *minishell, char *line, int fd)
{
	char	**args;

	args = miniparse(minishell, line);
	if (args[0] == NULL)
	{
		gfree_double(args);
		return (gfree(line));
	}
	else if (args[0][0] == '\0')
	{
		gfree_double(args);
		return (gfree(line));
	}
	gfree(line);
	if (is_builtin(args) && is_piped())
		piped_builtin(minishell, args);
	else if (!builtin_functions(minishell, args, fd))
		try_launch(minishell, args);
	gfree_double(args);
	return ;
}

/*
** Check if the command is a builtin function
*/
t_bool	builtin_functions(t_minishell *minishell, char **args, int fd)
{
	if (ft_strcmp(args[0], "exit") == 0)
		exit(func_exit(args[1], minishell));
	else if (ft_strcmp(args[0], "echo") == 0)
		minishell->returns.exit_stat = func_echo(args, fd);
	else if (ft_strcmp(args[0], "cd") == 0)
		minishell->returns.exit_stat = func_cd(minishell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		minishell->returns.exit_stat = func_pwd(minishell, fd);
	else if (ft_strcmp(args[0], "export") == 0)
		minishell->returns.exit_stat = func_export(minishell, args, fd);
	else if (ft_strcmp(args[0], "unset") == 0)
		minishell->returns.exit_stat = func_unset(minishell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		minishell->returns.exit_stat = func_env(minishell, fd, 0);
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

	path = calc_bin_path(minishell, args);
	if (path != NULL)
	{
		launch_bin(minishell, path, args);
		gfree(path);
	}
	else
	{
		if (!is_piped())
			display_nf(args[0]);
		else
			fork_nf(minishell, args[0]);
		minishell->returns.exit_stat = 127;
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

	path = NULL;
	if (!ft_strncmp("./", args[0], 2))
		path = verif_file(ft_strfcat(ft_strfcat(minishell->pwd, "/", FALSE,
						FALSE), &args[0][2], TRUE, FALSE));
	else if (!ft_strncmp("~/", args[0], 2))
		path = verif_file(ft_strfcat(ft_strfcat(minishell->home, "/", FALSE,
						FALSE), &args[0][2], TRUE, FALSE));
	else if (!ft_strncmp("/", args[0], 1))
		path = verif_file(ft_strdup(args[0]));
	else if (get_env_value(minishell, "PATH") != NULL)
	{
		paths = gft_split(get_env_value(minishell, "PATH"), ':');
		path = search_binary(paths, args[0]);
		gfree_double(paths);
	}
	if (path != NULL)
		gman_add(path);
	return (path);
}
