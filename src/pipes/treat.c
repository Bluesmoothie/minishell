/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:49:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/12 17:25:32 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc(char *tmp, int pipefd1);

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

int	fill_here_doc(t_pipes *new, char *tmp)
{
	int		pipefd[2];
	int		pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (close(pipefd[0]) == -1)
			return (-1);
		run_heredoc(tmp, pipefd[1]);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipefd[0], new->fd_in);
		close(pipefd[0]);
	}
	return (pipefd[0]);
}

static void	run_heredoc(char *tmp, int pipefd1)
{
	char	*last_line;

	while (1)
	{
		write(STDOUT_FILENO, "heredoc >", 9);
		last_line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(last_line, tmp, ft_strlen(tmp)))
		{
			close(pipefd1);
			free(last_line);
			return ;
		}
		write(pipefd1, last_line, ft_strlen(last_line));
		free(last_line);
	}
}
