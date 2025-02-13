/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_protectors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:02:43 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 16:20:47 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Protection function use it normally
** without carrying about errors
*/
void	protec_open(t_minishell *minishell, const char *__file, int __oflag)
{
	int	code;

	code = open(__file, __oflag);
	if (code == -1)
		free_exit(minishell, E_OPEN);
}
