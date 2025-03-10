/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:27:04 by ygille            #+#    #+#             */
/*   Updated: 2025/03/10 11:37:04 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Exit with code in arg if present
*/
int	func_exit(char *arg, t_minishell *minishell)
{
	int	code;

	code = 0;
	if (arg)
		code = ft_atoi(arg);
	else
		code = minishell->last_return_value;
	gclean();
	return (code);
}
