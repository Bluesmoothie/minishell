/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:17:46 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/12 15:46:49 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	father(int *pipefd, int *pid, int size, t_minishell *minishell);
static void son(int i, t_pipes *current, int size, int *pipefd);
static int	pipe_and_fork(int *pipefd, int i);

void	multiple_pipes(t_minishell *minishell, t_pipes **unpiped, int size)
{
	int		*pipefd;
	int		*pid;
	int		i;
	t_pipes	*current;

	current = *unpiped;
	pipefd = (int *)malloc((2 * size) * sizeof(int));
	if (!pipefd)
		return ; //A TRAITER
	pid = (int *)malloc(size * sizeof(int));
	if (!pid)
		return ; //A TRAITER
	i = 0;
	while (current)
	{
		pid[i] = pipe_and_fork(pipefd, i);
		if (pid[i] == 0)
		{
			son(i, current, size, pipefd);
			treat_arguments(minishell, current->content, current->fd_out);
			exit(EXIT_SUCCESS);
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

	i = 0;
	while (i < 2 * size)
	{
		if (close(pipefd[i]) == -1)
			return ;
		if (i % 2 != 0)
			waitpid(pid[i / 2], &minishell->last_return_value, 0);
		i++;
	}
	free(pipefd);
	free(pid);
}

static void son(int i, t_pipes *current, int size, int *pipefd)
{	
	int j;
	
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
	while (j < 2 * size)
		close(pipefd[j++]);
}
