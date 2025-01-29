/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:29 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 17:24:46 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->envp[i] != NULL)
		ft_putendl_fd(minishell->envp[i++], 1);
	minishell->last_return_value = 0;
}
