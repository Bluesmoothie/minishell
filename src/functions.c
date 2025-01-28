/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:43:02 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 00:48:59 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_echo(char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	free(args);
}

void	func_cd(char *line)
{
	(void)line;
}

void	func_pwd(void)
{
	ft_putendl_fd(getenv("PWD"), 1);
}

void	func_export(char *line)
{
	(void)line;
}

void	func_unset(char *line)
{
	(void)line;
}
