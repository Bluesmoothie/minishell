/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:43:02 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 14:32:17 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_echo(char **args)
{
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

void	func_cd(char **args)
{
	char	*dir;

	if (args[1] == NULL || (args[1][0] == '~'
		&& ((args[1][1] == '/' && args[1][2] == '\0') || args[1][1] == '\0')))
		chdir(getenv("HOME"));
	else if (args[1][0] == '~' && args[1][1] == '/' && args[1][2] != '\0')
	{
		dir = ft_strdup(getenv("HOME"));
		dir = ft_strfcat(dir, &args[1][1], TRUE, FALSE);
		if (chdir(dir))
			display_error(args[0], E_NOFILE, args[1]);
		free(dir);
	}
	else if (chdir(args[1]))
		display_error(args[0], E_NOFILE, args[1]);
}

void	func_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}

void	func_export(char **args)
{
	(void)args;
}

void	func_unset(char **args)
{
	(void)args;
}
