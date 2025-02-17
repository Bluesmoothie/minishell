/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:19:06 by ygille            #+#    #+#             */
/*   Updated: 2025/02/17 16:48:23 by ygille           ###   ########.fr       */
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
		{
			pid_list = gmalloc(size + 1);
			pid_list[size] = 0;
		}
		pid_list[index] = pid;
	}
	else if (op_code == PRESET)
	{
		gfree(pid_list);
		pid_list = NULL;
	}
	return (pid_list);
}
