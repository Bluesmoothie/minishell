/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nf.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:56:07 by ygille            #+#    #+#             */
/*   Updated: 2025/03/18 16:03:23 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file(char *path);

int	fork_nf(t_minishell *minishell, char *comm)
{
	int			pid;
	t_pipe_mem	pipe;
	int			code;

	pipe = get_pipe();
	pid = 0;
	code = display_nf(comm);
	add_pid(pid, pipe.i, pipe.size);
	minishell->child_pid = pid;
	return (code);
}

int	display_nf(char *arg)
{
	int	code;

	if (!ft_strncmp("./", arg, 2) || !ft_strncmp("~/", arg, 2)
		|| !ft_strncmp("/", arg, 1))
	{
		code = check_file(arg);
		if (code == 1)
			display_error(arg, E_ISDIR, NULL);
		else if (code == 2)
			display_error(arg, E_PERM, NULL);
		if (code == 1 || code == 2)
			return (126);
		else
			display_error(arg, E_FILE, NULL);
	}
	else
		display_error(arg, E_COMMANDNF, NULL);
	return (127);
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
