/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:01 by ygille            #+#    #+#             */
/*   Updated: 2025/02/15 12:45:38 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the echo command, display a message
*/
int	func_echo(char **args, int fd)
{
	int		i;
	t_bool	newline;

	newline = TRUE;
	i = 1;
	if (args[i] == NULL)
	{
		ft_putchar_fd('\n', fd);
		return (0);
	}
	else if (ft_strcmp(args[i], "-n") == 0)
	{
		i++;
		newline = FALSE;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i++], fd);
		if (args[i] != NULL)
			ft_putchar_fd(' ', fd);
	}
	if (newline)
		ft_putchar_fd('\n', fd);
	return (0);
}
