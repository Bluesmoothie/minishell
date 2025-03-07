/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:46:14 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/06 17:42:45 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*update_env(char *str, int i, int j, t_minishell *minishell);

char	*treat_env(char *str, t_minishell *minishell)
{
	int		i;
	int		j;
	char	*result;
	char	*tmp;

	i = -1;
	j = 0;
	result = NULL;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, j, i - j);
			result = ft_strfcat(result, tmp, TRUE, TRUE);
			j = i;
			while (str[j] && str[j] != '\"' && str[j] != '\'' && str[j] != ' ')
				j++;
			tmp = update_env(str, i, j, minishell);
			result = ft_strfcat(result, tmp, TRUE, FALSE);
			i = j;
		}
	}
	if (i > j)
		result = ft_strfcat(result, str + j, TRUE, FALSE);
	return (result);
}

static char	*update_env(char *str, int i, int j, t_minishell *minishell)
{
	char	*tmp;
	char	*env;

	env = ft_substr(str, i + 1, j - i - 1);
	if (!env)
		return (gcall_exit(E_MALLOC), NULL);
	tmp = get_env_value(minishell, env);
	free(env);
	return (tmp);
}
