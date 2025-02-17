/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_connect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:11 by ygille            #+#    #+#             */
/*   Updated: 2025/02/17 15:33:32 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pipe_mem	pipe_int(t_pipe_mem pipe, int op_code);

t_bool	is_piped(void)
{
	static t_pipe_mem	pipe_null = {0, 0, 0, 0, FALSE};
	t_pipe_mem			pipe_get;

	pipe_get = pipe_int(pipe_null, PGET);
	return (pipe_get.is_piped);
}

void	set_pipe(int i, t_pipes *current, int size, int *pipefd)
{
	t_pipe_mem	to_mem;

	to_mem.i = i;
	to_mem.current = current;
	to_mem.size = size;
	to_mem.pipefd = pipefd;
	to_mem.is_piped = TRUE;
	pipe_int(to_mem, PSET);
}

void	reset_pipe(void)
{
	static t_pipe_mem	pipe_null = {0, 0, 0, 0, FALSE};

	pipe_int(pipe_null, PRESET);
}

t_pipe_mem	get_pipe(void)
{
	static t_pipe_mem	pipe_null = {0, 0, 0, 0, FALSE};

	return (pipe_int(pipe_null, PGET));
}

static t_pipe_mem	pipe_int(t_pipe_mem pipe, int op_code)
{
	static t_pipe_mem	pipe_mem = {0, 0, 0, 0, FALSE};
	static t_pipe_mem	pipe_null = {0, 0, 0, 0, FALSE};

	if (op_code == PSET)
		pipe_mem = pipe;
	else if (op_code == PRESET)
		pipe_mem.is_piped = FALSE;
	else if (op_code == PGET)
		return (pipe_mem);
	return (pipe_null);
}
