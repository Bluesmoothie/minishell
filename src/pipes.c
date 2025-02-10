/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:07:02 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/10 14:59:19 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	treat_pipe(t_minishell *minishell, char **unpiped, int i);

/*
Split line with pipes
creates children and executes commands inside
*/
void	unpipe(t_minishell *minishell, char *line)
{
	char	**unpiped;
	int		in;
	int		i;

	if (line == NULL)
		free_exit(minishell, NULL, NULL);
	unpiped = ft_split(line, '|');
	if (!unpiped)
		free_exit(minishell, unpiped, E_SPLITFAIL);
	if (!unpiped[0])
		return (free_split(&unpiped));
	if (!unpiped[1])
		return (free_split(&unpiped), treat_arguments(minishell, line, 1));
	in = dup(STDIN_FILENO);
	i = 0;
	while (unpiped[i])
	{
		treat_pipe(minishell, unpiped, i);
		i++;
	}
	dup2(in, STDIN_FILENO);
}

static void	treat_pipe(t_minishell *minishell, char **unpiped, int i)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
		return (free_exit(minishell, unpiped, E_FORKFAIL));
	if (pid == 0)
	{
		if (close(pipefd[0]) == -1)
			return (free_exit(minishell, unpiped, "Close failed"));
		if (unpiped[i + 1] && (dup2(pipefd[1], STDOUT_FILENO) == -1))
			return (free_exit(minishell, unpiped, "dup2 failed"));
		treat_arguments(minishell, unpiped[i], STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (unpiped[i + 1] && (dup2(pipefd[0], STDIN_FILENO) == -1))
			return (free_exit(minishell, unpiped, "dup2 failed"));
		if (waitpid(pid, NULL, 0) == -1)
			return (free_exit(minishell, unpiped, "waitpid failed"));
	}
	if (close(pipefd[1]) == -1)
		return (free_exit(minishell, unpiped, "close failed"));
}
