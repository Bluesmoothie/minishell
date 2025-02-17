/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:55:15 by ygille            #+#    #+#             */
/*   Updated: 2025/02/17 19:45:31 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	launch_pipe_builtin(t_minishell *minishell, char **args, int fd);

t_bool	is_builtin(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (TRUE);
	else if (ft_strcmp(args[0], "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(args[0], "export") == 0)
		return (TRUE);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(args[0], "env") == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	piped_builtin(t_minishell *minishell, char **args)
{
	int			pid;
	t_pipe_mem	pipe;

	pipe = get_pipe();
	pid = fork();
	if (pid == -1)
		gcall_exit(E_FORK);
	if (pid == 0)
	{
		son(pipe.i, pipe.current, pipe.size, pipe.pipefd);
		launch_pipe_builtin(minishell, args, pipe.current->fd_out);
	}
	add_pid(pid, pipe.i, pipe.size);
	minishell->child_pid = pid;
}

static void	launch_pipe_builtin(t_minishell *minishell, char **args, int fd)
{
	int	code;

	code = -1;
	if (ft_strcmp(args[0], "exit") == 0)
		code = 0;
	else if (ft_strcmp(args[0], "echo") == 0)
		code = func_echo(args, fd);
	else if (ft_strcmp(args[0], "cd") == 0)
		code = func_cd(minishell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		code = func_pwd(minishell, fd);
	else if (ft_strcmp(args[0], "export") == 0)
		code = func_export(minishell, args, fd);
	else if (ft_strcmp(args[0], "unset") == 0)
		code = func_unset(minishell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		code = func_env(minishell, fd, 0);
	exit (code);
}
