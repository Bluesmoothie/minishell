/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:17:46 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/04 17:01:16 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	father(int *pipefd, int *pid, int size, t_minishell *minishell);
// static void	treat_n_exit(t_minishell *minishell, char *line, int fd);
// void	son(int i, t_pipes *current, int size, int *pipefd);
// static int	pipe_and_fork(int *pipefd, int i);

void	multiple_pipes(t_minishell *minishell, t_pipes **unpiped, int size)
{
	int		*pipefd;
	int		*pid;
	int		i;
	t_pipes	*current;

	current = *unpiped;
	pipefd = (int *)gmalloc((2 * size) * sizeof(int));
	i = 0;
	while (current)
	{
		if (pipe(pipefd + 2 * i) == -1)
			return (gcall_exit(E_PIPE));
		set_pipe(i, current, size, pipefd);
		treat_arguments(minishell, current->content, current->fd_out);
		current = current->next;
		i++;
	}
	pid = get_pid();
	father(pipefd, pid, size, minishell);
	current = *unpiped;
	while (current)
	{
		if (!isatty(current->fd_in))
			close(current->fd_in);
		if (!isatty(current->fd_out))
			close(current->fd_out);
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
		if (close(pipefd[i]) == -1)
			return (gcall_exit(E_OPEN));
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

void	son(int i, t_pipes *current, int size, int *pipefd)
{
	int	j;

	if (current->fd_in != STDIN_FILENO && dup2(current->fd_in, STDIN_FILENO) == -1)
			exit (EXIT_FAILURE);
	if (current->fd_out != STDOUT_FILENO && dup2(current->fd_out, STDOUT_FILENO) == -1)
			exit (EXIT_FAILURE);
	if (i == 0)
	{
		if (dup2(pipefd[1], current->fd_out) == -1)
			exit(EXIT_FAILURE);
	}
	else if (i < size - 1)
	{
		if (dup2(pipefd[2 * (i - 1)], current->fd_in) == -1)
			exit(EXIT_FAILURE);
		if (dup2(pipefd[2 * i + 1], current->fd_out) == -1)
			exit(EXIT_FAILURE);
	}
	else if (dup2(pipefd[2 * (i - 1)], current->fd_in) == -1)
		exit(EXIT_FAILURE);
	j = 0;
	while (j < 2 * i + 2)
		if (close(pipefd[j++]) == -1)
			exit(EXIT_FAILURE);
}
