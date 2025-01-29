/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:38:14 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 01:28:23 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(char *line)
{
	char	**args;

	if (line == NULL)
		return ;
	args = ft_split(line, ' ');
	add_history(line);
	free(line);
	if (args == NULL)
		free_exit(args, E_SPLITFAIL);
	if (!builtin_functions(args))
		try_launch(args);
	free_split(args);
	return ;
}

t_bool	builtin_functions(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
		free_exit(args, NULL);
	else if (ft_strcmp(args[0], "echo") == 0)
		func_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		func_cd(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		func_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		func_export(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		func_unset(args);
	else if (ft_strcmp(args[0], "env") == 0)
		func_env();
	else
		return (FALSE);
	return (TRUE);
}

void	try_launch(char **args)
{
	(void)args;
}
