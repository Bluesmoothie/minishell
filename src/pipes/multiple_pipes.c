/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:17:46 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/11 16:23:54 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	father(int *pipefd, int *pid, int size, t_minishell *minishell);
static void	check_tty(t_pipes *current);
static void	pipe_check_ttys(t_pipes *current);

void	multiple_pipes(t_minishell *minishell, t_pipes **unpiped, int size)
{
	int		pipefd[2];
	int		i;
	t_pipes	*current;
	int		*fds;

	current = *unpiped;
	i = -1;
	while (current)
	{
		if (pipe(pipefd) == -1)
			return (gcall_exit(E_PIPE));
		if (current->next)
			current->next->piped_fd_out = pipefd[0];
		set_pipe(++i, current, size, pipefd);
		fds = establish_fd_list(current);
		treat_arguments(minishell, current->content, fds);
		close(pipefd[1]);
		if (!isatty(current->piped_fd_out))
			close(current->piped_fd_out);
		current = current->next;
	}
	father(pipefd, get_pid(), size, minishell);
	current = *unpiped;
	pipe_check_ttys(current);
	pipeclear(unpiped);
}

static void	pipe_check_ttys(t_pipes *current)
{
	while (current)
	{
		check_tty(current);
		current = current->next;
	}
}

static void	father(int *pipefd, int *pid, int size, t_minishell *minishell)
{
	int	j;

	close(pipefd[0]);
	close(pipefd[1]);
	j = 0;
	while (j < size)
	{
		if (pid[j] != 0)
		{
			if (waitpid(pid[j], &minishell->last_return_value, 0) == -1)
				return (gcall_exit(E_WAITPID));
			returns_process(minishell->last_return_value, &minishell->returns);
		}
		j++;
	}
	minishell->child_pid = 0;
	reset_pid();
	reset_pipe();
}

void	son(int i, t_pipes *pipe, int size, int *pipefd)
{
	if (pipe->fd_in != STDIN_FILENO && dup2(pipe->fd_in, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (pipe->fd_out != STDOUT_FILENO && \
		dup2(pipe->fd_out, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
	if (i == 0)
	{
		if (dup2(pipefd[1], pipe->fd_out) == -1)
			exit(EXIT_FAILURE);
	}
	else if (i < size - 1)
	{
		if (dup2(pipe->piped_fd_out, pipe->fd_in) == -1)
			exit(EXIT_FAILURE);
		if (dup2(pipefd[1], pipe->fd_out) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipe->piped_fd_out, pipe->fd_in) == -1)
			exit(EXIT_FAILURE);
	}
}

static void	check_tty(t_pipes *current)
{
	if (!isatty(current->fd_in))
		if (close(current->fd_in) == -1)
			gcall_exit(E_CLOSE);
	if (!isatty(current->fd_out))
		if (close(current->fd_out) == -1)
			gcall_exit(E_CLOSE);
}
