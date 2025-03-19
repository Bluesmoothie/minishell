/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:10:07 by ygille            #+#    #+#             */
/*   Updated: 2025/03/19 12:22:26 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	suit(int (*f)(t_minishell*, char**), t_minishell *minishell, char **args)
{
	if (args[2])
		return (f(minishell, &args[1]));
	return (0);
}
