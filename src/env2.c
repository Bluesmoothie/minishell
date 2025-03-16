/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:06:53 by ygille            #+#    #+#             */
/*   Updated: 2025/03/16 23:21:04 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwdvar(t_minishell *minishell)
{
	char	*tmp;

	tmp = ft_strdup(get_env_value(minishell, "PWD"));
	if (tmp)
		gman_add(tmp);
	replace_env(minishell, "OLDPWD", tmp);
	tmp = ft_strdup(minishell->pwd);
	if (tmp)
		gman_add(tmp);
	replace_env(minishell, "PWD", tmp);
}

void	update_content(t_mlist *arg)
{
	char	*tmp;

	if (arg->name)
	{
		tmp = arg->content;
		arg->content = gman_add(ft_strfcat(arg->content, arg->name,
					FALSE, FALSE));
		gfree(tmp);
	}
}
