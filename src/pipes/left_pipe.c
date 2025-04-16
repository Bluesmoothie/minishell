/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:17:44 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/16 16:04:51 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append(t_pipes *new, int pos, t_minishell *minishell);
static int	check_left_path(char *path);
static int	fail_return(t_pipes *new, char *message, int ret_value);

int	left_pipe(t_pipes *new, int pos, t_minishell *minishell,
		t_bool **quote_checker)
{
	char	*path;

	if (new->content[pos + 1] == '>' && (*quote_checker)++)
		return (append(new, pos, minishell));
	else
	{
		path = pipe_helper(new, pos, 1);
		if (!path)
			return (2);
		path = miniparse(minishell, path)[0];
		if (new->fd_out != STDOUT_FILENO)
			close(new->fd_out);
		if (check_left_path(path))
		{
			delete_after_pos(new, pos);
			new->fd_out = open_null_fd();
			new->fd_in = open_null_fd();
			return (1);
		}
		new->fd_out = open(path, O_CREAT | O_RDWR | O_TRUNC, 00744);
		if (new->fd_out == -1)
			return (fail_return(new, E_OPEN, 1));
	}
	return (0);
}

static int	append(t_pipes *new, int pos, t_minishell *minishell)
{
	char	*path;

	if (new->content[pos + 2] == '<' || new->content[pos + 2] == '>')
	{
		write(2, "Syntax error\n", 13);
		return (2);
	}
	path = pipe_helper(new, pos, 2);
	if (!path)
		return (2);
	path = miniparse(minishell, path)[0];
	if (check_left_path(path))
	{
		delete_after_pos(new, pos);
		new->fd_out = open_null_fd();
		new->fd_in = open_null_fd();
		return (1);
	}
	new->fd_out = open(path, O_CREAT | O_APPEND | O_RDWR, 00744);
	if (new->fd_out == -1)
		return (fail_return(new, E_OPEN, 2));
	return (0);
}

static int	are_there_directories(char *path)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (path[i])
	{
		if (path[i] == '/' && i != 0)
		{
			tmp = gman_add(ft_substr(path, j, i - j));
			if (access(tmp, F_OK | X_OK))
			{
				printf("%s : no such file or directory\n", path);
				gfree(tmp);
				return (1);
			}
			gfree(tmp);
			j = i;
		}
		i++;
	}
	return (0);
}

static int	check_left_path(char *path)
{
	t_stat	path_stat;

	if (are_there_directories(path))
		return (1);
	if (path != NULL)
	{
		if (access(path, F_OK | X_OK) == 0)
		{
			stat(path, &path_stat);
			if (S_ISDIR(path_stat.st_mode))
			{
				printf("%s can't open file: is a directory\n", path);
				return (1);
			}
		}
		else if (!access(path, F_OK) && access(path, X_OK))
		{
			printf("%s: permission denied\n", path);
			return (1);
		}
	}
	return (0);
}

static int	fail_return(t_pipes *new, char *message, int ret_value)
{
	printf("%s\n", message);
	new->fd_out = open_null_fd();
	new->fd_in = open_null_fd();
	return (ret_value);
}
