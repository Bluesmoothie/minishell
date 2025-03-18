/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:56 by ygille            #+#    #+#             */
/*   Updated: 2025/03/18 18:18:47 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the pwd command, display the current directory
*/
int	func_pwd(t_minishell *minishell)
{
	if (minishell->pwd)
		ft_putendl_fd(minishell->pwd, STDOUT_FILENO);
	else
		display_error("pwd", " : Don't know where I am :(",
			" Did you removed the current directory ?");
	return (0);
}
