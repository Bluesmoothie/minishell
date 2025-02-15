/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:17 by ygille            #+#    #+#             */
/*   Updated: 2025/02/15 13:05:51 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the cd command, change the current directory
*/
int	func_cd(t_minishell *minishell, char **args)
{
	char	*dir;
	int		err;

	if (args[1] == NULL || (args[1][0] == '~'
		&& ((args[1][1] == '/' && args[1][2] == '\0') || args[1][1] == '\0')))
		err = chdir(minishell->home);
	else if (args[1][0] == '~' && args[1][1] == '/' && args[1][2] != '\0')
	{
		dir = gman_add(ft_strfcat(minishell->home, &args[1][1], FALSE, FALSE));
		err = chdir(dir);
		gfree(dir);
	}
	else
		err = chdir(args[1]);
	if (err)
		display_error(args[0], E_NOFILE, args[1]);
	return (err);
}
