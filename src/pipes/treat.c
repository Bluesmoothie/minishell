/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:49:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/07 15:44:06 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_finished(char *s, char c);
static int		has_no_quotes(char *str);

int	fill_here_doc(t_pipes *new, char *tmp, t_minishell *minishell)
{
	int								pipefd[2];
	int								quoted;
	extern volatile sig_atomic_t	g_signaled;

	quoted = 1;
	if (!has_no_quotes(tmp))
		quoted = 0;
	else if (has_no_quotes(tmp) == -1)
		return (write(2, "Close your quotes!\n", 19));
	else
		tmp = gman_add(trimndelete(tmp, " \"\'"));
	pipe(pipefd);
	run_heredoc(tmp, pipefd[1], quoted, minishell);
	if (g_signaled == 0)
		new->fd_in = dup(pipefd[0]);
	close(pipefd[0]);
	if (new->fd_in == -1)
		gcall_exit(E_DUP);
	init_signals();
	return (0);
}

static int	has_no_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 && is_finished(&str[i], 34))
			return (1);
		else if (str[i] == 34)
			return (-1);
		else if (str[i] == 39 && is_finished(&str[i], 39))
			return (1);
		else if (str[i] == 39)
			return (-1);
		i++;
	}
	return (0);
}

static t_bool	is_finished(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
