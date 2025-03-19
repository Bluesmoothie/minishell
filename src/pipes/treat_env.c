/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:46:14 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/19 13:16:09 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*treat_env(char *str, t_minishell *minishell)
{
	t_mlist		arg;

	arg.content = str;
	arg.mask = ' ';
	arg.glue = FALSE;
	arg.next = NULL;
	search_for_env(minishell, &arg);
	return (arg.content);
}
