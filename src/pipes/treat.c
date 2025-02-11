/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:49:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/11 19:06:04 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	treat_pipe(t_minishell *minishell, t_pipes *unpiped)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
		return (free_exit(minishell, NULL, E_FORKFAIL));
	if (pid == 0)
	{
		if (close(pipefd[0]) == -1)
			return (free_exit(minishell, NULL, "Close failed"));
		if (unpiped->next && (dup2(pipefd[1], unpiped->fd_out) == -1))
			return (free_exit(minishell, NULL, "dup2 failed"));
		treat_arguments(minishell, unpiped->content, unpiped->fd_out);
		if (close(pipefd[1]) == -1)
			return (free_exit(minishell, NULL, "close failed"));		
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (unpiped->next && (dup2(pipefd[0], unpiped->fd_in) == -1))
			return (free_exit(minishell, NULL, "dup2 failed"));
		if (close(pipefd[1]) == -1)
			return (free_exit(minishell, NULL, "close failed"));
	}
	if (waitpid(pid, NULL, 0) == -1)
		return (free_exit(minishell, NULL, "waitpid failed"));
}
