/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:28:03 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/06 17:42:54 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_signal(int sig);
static void	heredoc_sig_father(int sig);
static void	son_heredoc(int *pipefd);
static int	heredoc_done(int r, char *last_line, int pipefd1, char *tmp);

void	run_heredoc(char *tmp, int pipefd1, int quoted, t_minishell *minishell)
{
	char	*last_line;
	pid_t	pid;
	int		pipefd[2];
	int		r;

	while (1)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
			son_heredoc(pipefd);
		signal(SIGINT, heredoc_sig_father);
		last_line = (char *)gmalloc(4097 * sizeof(char));
		close(pipefd[1]);
		r = read(pipefd[0], last_line, 4096);
		close(pipefd[0]);
		if (heredoc_done(r, last_line, pipefd1, tmp))
			return ;
		if (!quoted)
			last_line = treat_env(last_line, minishell);
		last_line = ft_strfcat(last_line, "\n", TRUE, FALSE);
		write(pipefd1, last_line, ft_strlen(last_line));
		gfree(last_line);
	}
}

static void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_SUCCESS);
}

static void	heredoc_sig_father(int sig)
{
	extern volatile sig_atomic_t	g_signaled;

	if (sig == SIGINT)
		g_signaled = 1;
}

static void	son_heredoc(int *pipefd)
{
	char	*last_line;

	signal(SIGINT, heredoc_signal);
	close(pipefd[0]);
	last_line = readline("heredoc >");
	write(pipefd[1], last_line, ft_strlen(last_line));
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

static int	heredoc_done(int r, char *last_line, int pipefd1, char *tmp)
{
	if (r < 1)
	{
		gfree(last_line);
		if (close(pipefd1) == -1)
			gcall_exit(E_CLOSE);
		return (1);
	}
	if (!ft_strcmp(last_line, tmp))
	{
		close(pipefd1);
		gfree(last_line);
		return (1);
	}
	return (0);
}
