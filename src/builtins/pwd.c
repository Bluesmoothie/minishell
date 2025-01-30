/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:56 by ygille            #+#    #+#             */
/*   Updated: 2025/01/30 16:24:17 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the pwd command, display the current directory
*/
int	func_pwd(t_minishell *minishell)
{
	ft_putendl_fd(minishell->pwd, 1);
	return (0);
}
