/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:44:17 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/16 16:20:57 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signaled;

static int				right_pipe(t_pipes *new, int pos,
							t_minishell *minishell, t_bool **quote_checker);
static int				right_pipe_2(char *path, t_pipes *new);
static int				check_if_continue(int j, t_pipes *new);

/*
checks the existence of < and >
and modifies the fd accordingly
*/

int	parse_pipe(t_pipes *new, t_minishell *minishell)
{
	int		i;
	int		j;
	t_bool	*q_c;

	i = -1;
	g_signaled = 0;
	q_c = quotes_verif_chevron(new->content);
	while (new->content[++i])
	{
		j = 0;
		if (new->content[i] && new->content[i] == '<' && *q_c++ == TRUE)
		{
			j = right_pipe(new, i, minishell, &q_c);
			i = -1;
		}
		else if (new->content[i] && new->content[i] == '>' && *q_c++ == TRUE)
		{
			j = left_pipe(new, i, minishell, &q_c);
			i = -1;
		}
		if (check_if_continue(j, new))
			return (check_if_continue(j, new));
	}
	gfree(q_c);
	return (0);
}

static int	check_if_continue(int j, t_pipes *new)
{
	extern volatile sig_atomic_t	g_signaled;

	if (j > 1 || g_signaled)
	{
		new->issue = 1;
		return (2);
	}
	if (j || g_signaled)
		return (1);
	return (0);
}

static int	right_pipe(t_pipes *new, int pos, t_minishell *minishell,
		t_bool **quote_checker)
{
	char	*path;

	if (new->content[pos + 1] == '<' && (*quote_checker)++)
	{
		if (new->content[pos + 2] == '<' || new->content[pos + 2] == '>')
			return (write(2, "Syntax error\n", 13));
		path = pipe_helper(new, pos, 2);
		if (!path)
			return (2);
		if (fill_here_doc(new, path, minishell))
			return (2);
	}
	else
	{
		if (!isatty(new->fd_in))
			close(new->fd_in);
		path = pipe_helper(new, pos, 1);
		if (!path)
			return (2);
		path = miniparse(minishell, path)[0];
		if (right_pipe_2(path, new))
			return (1);
	}
	return (0);
}

static int	right_pipe_2(char *path, t_pipes *new)
{
	if (access(path, F_OK))
	{
		new->skip = 1;
		new->fd_out = open_null_fd();
		printf("%s: No such file or directory\n", path);
		return (1);
	}
	if (access(path, R_OK))
	{
		new->skip = 1;
		new->fd_out = open_null_fd();
		printf("%s: permission denied\n", path);
		return (1);
	}
	if (check_path(path) == 1)
	{
		new->skip = 1;
		new->fd_out = open_null_fd();
		printf("can´t open file: is a directory\n");
		return (1);
	}
	new->fd_in = open(path, O_RDONLY);
	if (new->fd_in == -1)
		return (fail_return(new, E_OPEN, 1));
	return (0);
}

int	check_path(char *path)
{
	t_stat	path_stat;

	if (path != NULL)
	{
		if (access(path, F_OK | X_OK) == 0)
		{
			stat(path, &path_stat);
			if (S_ISDIR(path_stat.st_mode))
				return (1);
		}
		else if (access(path, F_OK) == 0)
			return (2);
	}
	return (3);
}
