/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:01 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 17:21:58 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_echo(t_minishell *minishell, char **args)
{
	int		i;
	t_bool	newline;

	newline = TRUE;
	i = 1;
	(void)minishell;
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
		echo_arg(minishell, &args[i]);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	minishell->last_return_value = 0;
}

void	echo_arg(t_minishell *minishell, char **args)
{
	char	*env;

	if (args[0][0] == '\0')
		return ;
	if (ft_strcmp(args[0], "$?") == 0)
		ft_putnbr_fd(minishell->last_return_value, 1);
	else if (args[0][0] == '$' && args[0][1] != '\0')
	{
		env = getenv(&args[0][1]);
		if (env != NULL)
			ft_putstr_fd(env, 1);
	}
	else
		ft_putstr_fd(args[0], 1);
	if (args[1] != NULL)
		ft_putchar_fd(' ', 1);
}
