/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:17:44 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/19 12:28:49 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append(t_pipes *new, int pos, t_minishell *minishell);

int	left_pipe(t_pipes *new, int pos, t_minishell *minishell, t_bool **quote_checker)
{
	char *path;
	
	if (new->content[pos + 1] == '>' && (*quote_checker)++)
	{
		if (append(new, pos, minishell))
			return (1);
	}
	else
	{
		path = pipe_helper(new, pos, 1);
		if (!path)
			return (1);
		path = miniparse(minishell, path)[0];
		if (check_path(path) == 1)
			return (printf("can´t open file: is a directory\n"));
		if (new->fd_out != STDOUT_FILENO)
			close(new->fd_out);
		new->fd_out = open(path, O_CREAT | O_RDWR | O_TRUNC, 00744);
		if (new->fd_out == -1)
			gcall_exit(E_OPEN);
	}
	return (0);
}

static int	append(t_pipes *new, int pos, t_minishell *minishell)
{
	char	*path;
	
	if (new->content[pos + 2] == '<' || new->content[pos + 2] == '>')
		return (write(2, "Syntax error\n", 13));
	path = pipe_helper(new, pos, 2);
	if (!path)
		return (1);
	path = miniparse(minishell, path)[0];
	if (check_path(path) == 1)
		return (printf("can´t open file: is a directory\n"));
	new->fd_out = open(path, O_CREAT | O_APPEND | O_RDWR, 00744);
	if (new->fd_out == -1)
		gcall_exit(E_OPEN);
	return (0);
}