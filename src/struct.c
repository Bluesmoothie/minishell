/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:45:43 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 15:00:07 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_minishell *minishell)
{
	minishell->home = getenv("HOME");
	minishell->user = getenv("USER");
	minishell->pwd = getcwd(NULL, 0);
	minishell->path = ft_split(getenv("PATH"), ':');
}

void	free_struct(t_minishell *minishell)
{
	if (minishell->pwd)
	{
		free(minishell->pwd);
		minishell->pwd = NULL;
	}
	if (minishell->path)
		free_split(&minishell->path);
}

void	update_infos(t_minishell *minishell)
{
	free_struct(minishell);
	init_struct(minishell);
}
