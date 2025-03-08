/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:56 by ygille            #+#    #+#             */
/*   Updated: 2025/03/08 12:30:13 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the pwd command, display the current directory
*/
int	func_pwd(t_minishell *minishell, int fd)
{
	if (minishell->pwd)
		ft_putendl_fd(minishell->pwd, fd);
	else
		display_error("pwd", " : Don't know where I am :(", NULL);
	return (0);
}
