/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:17:46 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/19 11:38:50 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	father(int *pipefd, int *pid, int size, t_minishell *minishell);
static void	check_tty(t_pipes *current);

void	multiple_pipes(t_minishell *minishell, t_pipes **unpiped, int size)
{
	int		*pipefd;
	int		i;
	t_pipes	*current;
	int		*fds;

	current = *unpiped;
	pipefd = (int *)gmalloc((2 * size) * sizeof(int));
	i = -1;
	fds = establish_fd_list(current);
	while (current)
	{
		if (pipe(pipefd + 2 * ++i) == -1)
			return (gcall_exit(E_PIPE));
		set_pipe(i, current, size, pipefd);
		treat_arguments(minishell, current->content, fds);
		current = current->next;
	}
	father(pipefd, get_pid(), size, minishell);
	current = *unpiped;
	while (current)
	{
		check_tty(current);
		current = current->next;
	}
	pipeclear(unpiped);
}

static void	father(int *pipefd, int *pid, int size, t_minishell *minishell)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2 * size)
	{
		close(pipefd[i]);
		i++;
	}
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
	gfree(pipefd);
	reset_pid();
	reset_pipe();
}

void	son(int i, t_pipes *pipe, int size, int *pipefd)
{
	int	j;

	if (pipe->fd_in != STDIN_FILENO && dup2(pipe->fd_in, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (pipe->fd_out != STDOUT_FILENO && \
		dup2(pipe->fd_out, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (i == 0)
	{
		if (dup2(pipefd[1], pipe->fd_out) == -1)
			exit(EXIT_FAILURE);
	}
	else if (i < size - 1)
	{
		if (dup2(pipefd[2 * (i - 1)], pipe->fd_in) == -1)
			exit(EXIT_FAILURE);
		if (dup2(pipefd[2 * i + 1], pipe->fd_out) == -1)
			exit(EXIT_FAILURE);
	}
	else if (dup2(pipefd[2 * (i - 1)], pipe->fd_in) == -1)
		exit(EXIT_FAILURE);
	j = 0;
	while (j < 2 * i + 2)
		close(pipefd[j++]);
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
