/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:07:02 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/10 13:53:07 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Split line with pipes
creates child and executes first command inside
continue until no more pipes
execute result
*/
void	unpipe(t_minishell *minishell, char *line)
{
	char	**unpiped;
	int		pipefd[2];
	int		in;
	int		pid;
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
	i = 0;
	in = dup(STDIN_FILENO);
	while (unpiped[i])
	{
		pipe(pipefd);
		pid = fork();
		// if pid == -1
		// return (error);
		if (pid == 0)
		{
			close(pipefd[0]);
			if (unpiped[i + 1])
				dup2(pipefd[1], STDOUT_FILENO);
			treat_arguments(minishell, unpiped[i], STDOUT_FILENO);
			close(pipefd[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(pipefd[1]);
			if (unpiped[i + 1])
				dup2(pipefd[0], STDIN_FILENO);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
	dup2(in, STDIN_FILENO);
}
