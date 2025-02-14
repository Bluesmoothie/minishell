/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:49:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/14 23:46:12 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc(char *tmp, int pipefd1);

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
			gfree(last_line);
			return ;
		}
		write(pipefd1, last_line, ft_strlen(last_line));
		gfree(last_line);
	}
}
