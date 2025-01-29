/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:17 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 17:21:03 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_cd(t_minishell *minishell, char **args)
{
	char	*dir;
	int		err;

	if (args[1] == NULL || (args[1][0] == '~'
		&& ((args[1][1] == '/' && args[1][2] == '\0') || args[1][1] == '\0')))
		err = chdir(minishell->home);
	else if (args[1][0] == '~' && args[1][1] == '/' && args[1][2] != '\0')
	{
		dir = ft_strfcat(minishell->home, &args[1][1], FALSE, FALSE);
		err = chdir(dir);
		free(dir);
	}
	else
		err = chdir(args[1]);
	if (err)
		display_error(args[0], E_NOFILE, args[1]);
	minishell->last_return_value = err;
}
