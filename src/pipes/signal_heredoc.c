/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:28:03 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/08 12:24:20 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sig_father(int sig);
static int	event_hook(void);
static int	heredoc_done(char *last_line, int pipefd1, char *tmp);

void	run_heredoc(char *tmp, int pipefd1, int quoted, t_minishell *minishell)
{
	char							*last_line;

	rl_event_hook = event_hook;
	while (1)
	{
		signal(SIGINT, heredoc_sig_father);
		last_line = readline("heredoc >");
		if (heredoc_done(last_line, pipefd1, tmp))
			return ;
		if (!quoted)
			last_line = treat_env(last_line, minishell);
		last_line = ft_strfcat(last_line, "\n", TRUE, FALSE);
		write(pipefd1, last_line, ft_strlen(last_line));
		gfree(last_line);
	}
}

static int	event_hook(void)
{
	extern volatile sig_atomic_t	g_signaled;

	if (g_signaled == 1)
	{
		rl_done = 1;
		return (0);
	}
	return (1);
}

static void	heredoc_sig_father(int sig)
{
	extern volatile sig_atomic_t	g_signaled;

	if (sig == SIGINT)
		g_signaled = 1;
}

static int	heredoc_done(char *last_line, int pipefd1, char *tmp)
{
	extern volatile sig_atomic_t	g_signaled;

	if (g_signaled)
	{
		free(last_line);
		g_signaled = 2;
		rl_done = 0;
		if (close(pipefd1) == -1)
			gcall_exit(E_CLOSE);
		return (1);
	}
	if (!last_line)
	{
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
