/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:27:04 by ygille            #+#    #+#             */
/*   Updated: 2025/03/06 17:48:15 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Exit with code in arg if present
*/
int	func_exit(char *arg)
{
	int	code;

	code = 0;
	if (arg)
		code = ft_atoi(arg);
	gclean();
	return (code);
}
