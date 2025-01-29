/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:56 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 17:17:41 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_pwd(t_minishell *minishell)
{
	ft_putendl_fd(minishell->pwd, 1);
	minishell->last_return_value = 0;
}
