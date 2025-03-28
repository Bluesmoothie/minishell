/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:55:15 by ygille            #+#    #+#             */
/*   Updated: 2025/03/19 12:50:02 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	launch_pipe_builtin(t_minishell *minishell, char **args);

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

void	piped_builtin(t_minishell *minishell, char **args, int *fds)
{
	int			pid;
	t_pipe_mem	pipe;
	int			code;
	int			i;

	pipe = get_pipe();
	pid = fork();
	if (pid == -1)
		gcall_exit(E_FORK);
	if (pid == 0)
	{
		son(pipe.i, pipe.current, pipe.size, pipe.pipefd);
		code = launch_pipe_builtin(minishell, args);
		i = 0;
		while (fds && fds[i] != 0)
		{
			close(fds[i]);
			i++;
		}
		gclean();
		exit (code);
	}
	add_pid(pid, pipe.i, pipe.size);
	minishell->child_pid = pid;
}

static int	launch_pipe_builtin(t_minishell *minishell, char **args)
{
	int	code;

	code = -1;
	if (ft_strcmp(args[0], "exit") == 0)
		code = func_exit(args[1], minishell);
	else if (ft_strcmp(args[0], "echo") == 0)
		code = func_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		code = func_cd(minishell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		code = func_pwd(minishell);
	else if (ft_strcmp(args[0], "export") == 0)
		code = func_export(minishell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		code = func_unset(minishell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		code = func_env(minishell, 0);
	return (code);
}
