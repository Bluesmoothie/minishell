/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:01 by ygille            #+#    #+#             */
/*   Updated: 2025/03/18 18:15:29 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	skip_args(int *i, char **args);

/*
** Like the echo command, display a message
*/
int	func_echo(char **args)
{
	int		i;
	t_bool	newline;

	newline = TRUE;
	i = 1;
	if (args[i] == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	newline = skip_args(&i, args);
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i++], STDOUT_FILENO);
		if (args[i] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/*
** To skip all -n
*/
static t_bool	skip_args(int *i, char **args)
{
	t_bool	ret;
	int		j;

	ret = TRUE;
	while (args[*i] != NULL)
	{
		if (ft_strncmp(args[*i], "-n", 2) == 0)
		{
			j = 2;
			while (args[*i][j] != '\0' && args[*i][j] == 'n')
				j++;
			if (args[*i][j] != '\0')
				break ;
			else
				ret = FALSE;
		}
		else
			break ;
		(*i)++;
	}
	return (ret);
}
