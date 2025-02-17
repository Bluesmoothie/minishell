/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:17:46 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/17 17:44:29 by ygille           ###   ########.fr       */
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
	pipeclear(unpiped);
}

// static int	pipe_and_fork(int *pipefd, int i)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return (gcall_exit(E_FORK), -1);
// 	return (pid);
// }

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
		if (waitpid(pid[j], &minishell->last_return_value, 0) == -1)
			return (gcall_exit(E_WAITPID));
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

// static void	treat_n_exit(t_minishell *minishell, char *line, int fd)
// {
// 	treat_arguments(minishell, line, fd);
// 	gcall_exit(EXIT_SUCCESS);
// }
