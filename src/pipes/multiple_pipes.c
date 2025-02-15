/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:17:46 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/15 21:14:47 by ygille           ###   ########.fr       */
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
	pid = (int *)gmalloc(size * sizeof(int));
	i = 0;
	while (current)
	{
		pid[i] = pipe_and_fork(pipefd, i);
		if (pid[i] == -1)
			gcall_exit("fork error\n");
		if (pid[i] == 0)
		{
			son(i, current, size, pipefd);
			treat_n_exit(minishell, current->content, current->fd_out);
		}
		current = current->next;
		i++;
	}
	father(pipefd, pid, size, minishell);
}

static int	pipe_and_fork(int *pipefd, int i)
{
	int	pid;

	if (pipe(pipefd + 2 * i) == -1)
		return (-1); //A TRAITER
	pid = fork();
	if (pid == -1)
		return (-1); // A TRAITER
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
			return ;
		i++;
	}
	j = 0;
	while (j < size)
	{
		waitpid(pid[j], NULL, 0);
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
			exit (EXIT_FAILURE);//A TRAITER
	}
	else if (i < size - 1) //peloton
	{
		if (dup2(pipefd[2 * (i - 1)], current->fd_in) == -1)
			exit (EXIT_FAILURE); // A TRAITER
		if (dup2(pipefd[2 * i + 1], current->fd_out) == -1)
			exit (EXIT_FAILURE); // A TRAITER
	}
	else if (dup2(pipefd[2 * (i - 1)], current->fd_in) == -1)
		exit (EXIT_FAILURE); //A TRAITER
	j = 0;
	while (j < 2 * i + 2)
		close(pipefd[j++]);
}

static void	treat_n_exit(t_minishell *minishell, char *line, int fd)
{
	treat_arguments(minishell, line, fd);
	exit(EXIT_SUCCESS);
}
