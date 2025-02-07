/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:07:02 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/07 18:24:29 by sithomas         ###   ########.fr       */
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
	int 	pipefd[2];
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
	while (unpiped[i + 1])
	{
		pipe(pipefd);
		pid = fork();
		//if pid == -1
			//return error;
		if (pid == 0)
		{
			close(pipefd[0]);
			dup2(1, pipefd[1]);
			// close(1);
			treat_arguments(minishell, unpiped[i], pipefd[1]);
			close(pipefd[1]);
		}
		else
		{
			close(pipefd[1]);
			dup2(pipefd[0], 0);
			// close(0);
			close(pipefd[0]);
		}
		i++;
	}
	wait(NULL);
	treat_arguments(minishell, unpiped[i], 1);
}
