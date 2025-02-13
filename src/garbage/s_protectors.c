/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_protectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:58:45 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 16:20:35 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Protection function use it normally
** without carrying about errors
*/
void	protec_pipe(t_minishell *minishell, int *__pipesdes)
{
	int	code;

	code = pipe(__pipesdes);
	if (code == -1)
		free_exit(minishell, E_PIPE);
}

/*
** Protection function use it normally
** without carrying about errors
*/
void	protec_close(t_minishell *minishell, int fd)
{
	int	code;

	code = close(fd);
	if (code == -1)
		free_exit(minishell, E_CLOSE);
}

/*
** Protection function use it normally
** without carrying about errors
** return the return code of the pid
*/
int	protec_waitpid(t_minishell *minishell, pid_t pid)
{
	pid_t	code;
	int		return_code;

	code = waitpid(pid, &return_code, 0);
	if (code == -1)
		free_exit(minishell, E_WAITPID);
	return (return_code);
}

/*
** Protection function use it normally
** without carrying about errors
*/
int	protec_dup(t_minishell *minishell, int __fd)
{
	int	code;

	code = dup(__fd);
	if (code == -1)
		free_exit(minishell, E_DUP);
	return (code);
}

/*
** Protection function use it normally
** without carrying about errors
*/
void	protec_dup2(t_minishell *minishell, int __fd, int __fd2)
{
	int	code;

	code = dup2(__fd, __fd2);
	if (code == -1)
		free_exit(minishell, E_DUP2);
}
