/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:17 by ygille            #+#    #+#             */
/*   Updated: 2025/03/16 23:21:59 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*calc_dir(t_minishell *minishell, char **args,
				t_bool *no_home_flag);
static int	no_home(void);

/*
** Like the cd command, change the current directory
*/
int	func_cd(t_minishell *minishell, char **args)
{
	char	*dir;
	int		err;
	t_bool	no_home_flag;

	no_home_flag = FALSE;
	err = 0;
	dir = calc_dir(minishell, args, &no_home_flag);
	if (no_home_flag)
		return (no_home());
	else if (dir)
		err = chdir(dir);
	else if (ft_strcmp(args[1], "-"))
		err = chdir(args[1]);
	if (err)
		display_error(args[0], E_NOFILE, args[1]);
	return (err);
}

static char	*calc_dir(t_minishell *minishell, char **args, t_bool *no_home_flag)
{
	char	*dir;

	dir = NULL;
	if (args[1] == NULL || (args[1][0] == '~'
		&& ((args[1][1] == '/' && args[1][2] == '\0') || args[1][1] == '\0')))
	{
		if (minishell->home == NULL)
			*no_home_flag = TRUE;
		else
			dir = gman_add(ft_strdup(minishell->home));
	}
	else if (args[1][0] == '~' && args[1][1] == '/' && args[1][2] != '\0')
	{
		if (minishell->home == NULL)
			*no_home_flag = TRUE;
		else
			dir = gman_add(ft_strfcat(minishell->home, &args[1][1],
						FALSE, FALSE));
	}
	return (dir);
}

static int	no_home(void)
{
	display_error("cd :", "No HOME set", NULL);
	return (1);
}
