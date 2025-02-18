/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:49:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/18 18:59:33 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc(char *tmp, int pipefd1);

int	fill_here_doc(int fd_in, char *tmp)
{
	int		pipefd[2];

	pipe(pipefd);
	run_heredoc(tmp, pipefd[1]);
	dup2(pipefd[0], fd_in);
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
