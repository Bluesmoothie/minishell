/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nf.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:56:07 by ygille            #+#    #+#             */
/*   Updated: 2025/03/10 13:05:32 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_nf(t_minishell *minishell, char *comm)
{
	int			pid;
	t_pipe_mem	pipe;

	pipe = get_pipe();
	pid = 0;
	display_nf(comm);
	add_pid(pid, pipe.i, pipe.size);
	minishell->child_pid = pid;
}

void	display_nf(char *arg)
{
	if (!ft_strncmp("./", arg, 2) || !ft_strncmp("~/", arg, 2)
		|| !ft_strncmp("/", arg, 1))
		display_error(arg, E_FILEOPERM, NULL);
	else
		display_error(arg, E_COMMANDNF, NULL);
}
