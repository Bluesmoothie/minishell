/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:55:15 by ygille            #+#    #+#             */
/*   Updated: 2025/03/10 11:38:10 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	launch_pipe_builtin(t_minishell *minishell, char **args, int fd);

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
	int			code;

	pipe = get_pipe();
	pid = fork();
	if (pid == -1)
		gcall_exit(E_FORK);
	if (pid == 0)
	{
		son(pipe.i, pipe.current, pipe.size, pipe.pipefd);
		code = launch_pipe_builtin(minishell, args, pipe.current->fd_out);
		gclean();
		exit (code);
	}
	add_pid(pid, pipe.i, pipe.size);
	minishell->child_pid = pid;
}

static int	launch_pipe_builtin(t_minishell *minishell, char **args, int fd)
{
	int	code;

	code = -1;
	if (ft_strcmp(args[0], "exit") == 0)
		code = func_exit(args[1], minishell);
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
	return (code);
}
