/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:44:17 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/18 17:55:44 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signaled;

static int	right_pipe(t_pipes *new, int pos, t_minishell *minishell,
				t_bool **quote_checker);
static int	left_pipe(t_pipes *new, int pos, t_bool **quote_checker);
static char	*pipe_helper(t_pipes *new, int pos, int param);
static int	right_pipe_2(char *path, t_pipes *new);
static int	check_file(char *path);

/*
checks the existence of < and > 
and modifies the fd accordingly
*/

int	parse_pipe(t_pipes	*new, t_minishell *minishell)
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
			j = left_pipe(new, i, &q_c);
			i = -1;
		}
		if (j || g_signaled)
			return (new->issue = 1);
	}
	gfree(q_c);
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
			return (1);
		if (fill_here_doc(new, path, minishell))
			return (1);
	}
	else
	{
		if (new->fd_in != STDIN_FILENO)
			close(new->fd_in);
		path = pipe_helper(new, pos, 1);
		if (!path)
			return (1);
		if (right_pipe_2(path, new))
			return (1);
	}
	return (0);
}

static int	left_pipe(t_pipes *new, int pos, t_bool **quote_checker)
{
	char	*path;

	if (new->content[pos + 1] == '>' && (*quote_checker)++)
	{
		if (new->content[pos + 2] == '<' || new->content[pos + 2] == '>')
			return (write(2, "Syntax error\n", 13));
		path = pipe_helper(new, pos, 2);
		if (!path)
			return (1);
		if (check_file(path) == 1)
			return (printf("can´t open file: is a directory\n"));
		new->fd_out = open(path, O_CREAT | O_APPEND | O_RDWR, 00744);
		if (new->fd_out == -1)
			gcall_exit(E_OPEN);
	}
	else
	{
		path = pipe_helper(new, pos, 1);
		if (!path)
			return (1);
		if (check_file(path) == 1)
			return (printf("can´t open file: is a directory\n"));
		if (new->fd_out != STDOUT_FILENO)
			close(new->fd_out);
		new->fd_out = open(path, O_CREAT | O_RDWR | O_TRUNC, 00744);
		if (new->fd_out == -1)
			gcall_exit(E_OPEN);
	}
	return (0);
}

static char	*pipe_helper(t_pipes *new, int pos, int param)
{
	int		j;
	char	**result;
	char	*path;

	j = pos + param;
	if (new->content[j] == ' ')
		while (new->content[j] == ' ')
			j++;
	if (!new->content[j] || new->content[j] == '<' || new->content[j] == '>')
		return ((void)write(2, "Syntax error\n", 13), NULL);
	while (new->content[j] && new->content[j] != '<'
		&& new->content[j] != '>' && new->content[j] != ' ')
		j++;
	result = extract_str(new->content, pos, j);
	new->content = gman_add(ft_strdup(result[0]));
	path = gman_add(ft_strtrim(result[1], "< >"));
	gfree_double(result);
	return (path);
}

static int	right_pipe_2(char *path, t_pipes *new)
{
	if (access(path, F_OK))
		return (printf("%s: No such file or directory\n", path));
	if (access(path, R_OK))
		return (printf("%s: permission denied\n", path));
	new->fd_in = open(path, O_RDONLY);
	if (new->fd_in == -1)
		gcall_exit(E_OPEN);
	return (0);
}


static int	check_file(char *path)
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