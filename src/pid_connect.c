/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:19:06 by ygille            #+#    #+#             */
/*   Updated: 2025/02/17 18:28:22 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*pid_int(int pid, int index, int size, int op_code);

void	add_pid(int pid, int index, int size)
{
	pid_int(pid, index, size, PSET);
}

void	reset_pid(void)
{
	pid_int(0, 0, 0, PRESET);
}

int	*get_pid(void)
{
	return (pid_int(0, 0, 0, PGET));
}

static int	*pid_int(int pid, int index, int size, int op_code)
{
	static int	*pid_list = NULL;

	if (op_code == PSET)
	{
		if (pid_list == NULL)
			pid_list = (int *)gmalloc(size * sizeof(int));
		pid_list[index] = pid;
	}
	else if (op_code == PRESET)
	{
		gfree(pid_list);
		pid_list = NULL;
	}
	return (pid_list);
}
