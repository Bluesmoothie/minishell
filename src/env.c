/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:13:22 by ygille            #+#    #+#             */
/*   Updated: 2025/02/06 18:13:40 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Search for environment variables in the arguments
** and replace them with their value
*/
void	search_for_env(t_minishell *minishell, char ***args)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*args)[i] != NULL)
	{
		if ((*args)[i][0] == '$' && (*args)[i][1] != '\0')
		{
			tmp = (*args)[i];
			(*args)[i] = get_env_value(minishell, &tmp[1]);
			free(tmp);
		}
		i++;
	}
}

/*
** Get the value of an environment variable
*/
char	*get_env_value(t_minishell *minishell, char *arg)
{
	t_mlist	*mlist;

	if (ft_strcmp(arg, "?") == 0)
		return (ft_itoa(minishell->last_return_value));
	mlist = minishell->env;
	while (mlist != NULL)
	{
		if (ft_strcmp(mlist->name, arg) == 0)
			return (mlist->content);
		mlist = mlist->next;
	}
	return (NULL);
}
