/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:06:53 by ygille            #+#    #+#             */
/*   Updated: 2025/02/19 15:13:09 by ygille           ###   ########.fr       */
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
