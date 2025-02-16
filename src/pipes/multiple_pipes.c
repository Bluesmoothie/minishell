/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:17:46 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/16 16:31:02 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	father(int *pipefd, int *pid, int size, t_minishell *minishell);
static void	treat_n_exit(t_minishell *minishell, char *line, int fd);
static void	son(int i, t_pipes *current, int size, int *pipefd);
static int	pipe_and_fork(int *pipefd, int i);

void	multiple_pipes(t_minishell *minishell, t_pipes **unpiped, int size)
{
	int		*pipefd;
	int		*pid;
	int		i;
	t_pipes	*current;

	current = *unpiped;
	pipefd = (int *)gmalloc((2 * size) * sizeof(int));
	pid = (int *)gmalloc((size) * sizeof(int));
	i = 0;
	while (current)
	{
		pid[i] = pipe_and_fork(pipefd, i);
		if (pid[i] == 0)
		{
			son(i, current, size, pipefd);
			treat_n_exit(minishell, current->content, current->fd_out);
		}
		current = current->next;
		i++;
	}
	father(pipefd, pid, size, minishell);
	pipeclear(unpiped);
}

static int	pipe_and_fork(int *pipefd, int i)
{
	int	pid;

	if (pipe(pipefd + 2 * i) == -1)
		return (gcall_exit(E_PIPE), -1);
	pid = fork();
	if (pid == -1)
		return (gcall_exit(E_FORK), -1);
	return (pid);
}

static void	father(int *pipefd, int *pid, int size, t_minishell *minishell)
{
	int	i;
	int	j;

	i = 0;
	(void)minishell;
	while (i < 2 * size)
	{
		if (close(pipefd[i]) == -1)
			return (gcall_exit(E_OPEN));
		i++;
	}
	j = 0;
	while (j < size)
	{
		if (waitpid(pid[j], NULL, 0) == -1)
			return (gcall_exit(E_WAITPID));
		j++;
	}
	gfree(pipefd);
	gfree(pid);
}

static void	son(int i, t_pipes *current, int size, int *pipefd)
{
	int	j;

	if (i == 0)
	{
		if (dup2(pipefd[1], current->fd_out) == -1)
			gcall_exit (E_DUP2);//A TRAITER
	}
	else if (i < size - 1)
	{
		if (dup2(pipefd[2 * (i - 1)], current->fd_in) == -1)
			gcall_exit (E_DUP2); // A TRAITER
		if (dup2(pipefd[2 * i + 1], current->fd_out) == -1)
			gcall_exit (E_DUP2); // A TRAITER
	}
	else if (dup2(pipefd[2 * (i - 1)], current->fd_in) == -1)
		gcall_exit (E_DUP2); //A TRAITER
	j = 0;
	while (j < 2 * i + 2)
		if (close(pipefd[j++]) == -1)
			gcall_exit(E_CLOSE);
	gfree(pipefd);
}

static void	treat_n_exit(t_minishell *minishell, char *line, int fd)
{
	treat_arguments(minishell, line, fd);
	gcall_exit(EXIT_SUCCESS);
}
