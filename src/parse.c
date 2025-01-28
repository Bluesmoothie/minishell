/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:38:14 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 00:49:34 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(char *line)
{
	if (line == NULL)
		return ;
	add_history(line);
	if (!builtin_functions(line))
		try_launch(line);
	free(line);
	return ;
}

t_bool	builtin_functions(char *line)
{
	if (ft_strcmp(line, "exit") == 0)
		free_exit(line);
	else if (ft_strcmp(line, "echo") == 0)
		func_echo(line);
	else if (ft_strcmp(line, "cd") == 0)
		func_cd(line);
	else if (ft_strcmp(line, "pwd") == 0)
		func_pwd();
	else if (ft_strcmp(line, "export") == 0)
		func_export(line);
	else if (ft_strcmp(line, "unset") == 0)
		func_unset(line);
	else if (ft_strcmp(line, "env") == 0)
		func_env();
	else
		return (FALSE);
	return (TRUE);
}

void	try_launch(char *line)
{
	(void)line;
}
