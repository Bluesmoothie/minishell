/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:17 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 15:13:23 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_cd(t_minishell *minishell, char **args)
{
	char	*dir;

	if (args[1] == NULL || (args[1][0] == '~'
		&& ((args[1][1] == '/' && args[1][2] == '\0') || args[1][1] == '\0')))
		chdir(minishell->home);
	else if (args[1][0] == '~' && args[1][1] == '/' && args[1][2] != '\0')
	{
		dir = ft_strfcat(minishell->home, &args[1][1], FALSE, FALSE);
		if (chdir(dir))
			display_error(args[0], E_NOFILE, args[1]);
		free(dir);
	}
	else if (chdir(args[1]))
		display_error(args[0], E_NOFILE, args[1]);
}
