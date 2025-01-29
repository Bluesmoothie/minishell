/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:01 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 15:13:08 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_echo(t_minishell *minishell, char **args)
{
	(void)minishell;
	int		i;
	t_bool	newline;

	newline = TRUE;
	i = 1;
	if (args[i] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	else if (ft_strcmp(args[i], "-n") == 0)
	{
		i++;
		newline = FALSE;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}
