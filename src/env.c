/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:13:22 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 17:21:59 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Search for environment variables in the arguments
** and replace them with their value
*/
void	search_for_env(t_minishell *minishell, t_mlist *args)
{
	char	*start;
	char	*env_name;
	char	*val;

	while (args != NULL)
	{
		if (args->mask != '\'' && ft_strchr(args->content, '$') != NULL)
		{
			args->name = args->content;
			args->content = NULL;
			start = ft_strchr(args->name, '$');
			while (start != NULL)
			{
				env_name = get_env_name(minishell, &start[1]);
				val = get_env_value(minishell, env_name);
				replace_env_value(minishell, args, val);
				start = ft_strchr(args->name, '$');
			}
			garbage_release (minishell, args->name);
			start = NULL;
			val = NULL;
		}
		args = args->next;
	}
}

/*
** Return the frist found env name from the passed arg
*/
char	*get_env_name(t_minishell *minishell, char *arg)
{
	int		i;
	char	*result;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '$')
		i++;
	result = garbage_malloc(minishell, sizeof(char) * i);
	result[i] = '\0';
	while (i--)
		result[i] = arg[i];
	return (result);
}

/*
** Get the value of an environment variable
*/
char	*get_env_value(t_minishell *minishell, char *arg)
{
	t_mlist	*mlist;

	if (ft_strcmp(arg, "?") == 0)
		return (garbage_itoa(minishell, minishell->last_return_value));
	mlist = minishell->env;
	while (mlist != NULL)
	{
		if (ft_strcmp(mlist->name, arg) == 0)
			return (mlist->content);
		mlist = mlist->next;
	}
	return (NULL);
}

/*
** Replace value in node by it's found value in the env variables
*/
void	replace_env_value(t_minishell *minishell, t_mlist *node, char *value)
{
	int		i;
	char	*result;

	i = 0;
	while (node->name[i] != '$')
		i++;
	if (i > 0)
	{
		result = garbage_substr(minishell, node->name, 0, i);
		result = garbage_strfcat(minishell, result, value, 10);
	}
	else
		result = garbage_strdup(minishell, value);
	node->content = garbage_strjoin(minishell, node->content, result);
	node->name = update_searching(minishell, node->name, i + 1);
}

/*
** Update name to permit others env var to be found
*/
char	*update_searching(t_minishell *minishell, char *name, int i)
{
	char	*result;

	result = NULL;
	while (name[i] != '\0' && name[i] != '$')
		i++;
	if (name[i] == '\0')
		garbage_release(minishell, name);
	else
	{
		result = garbage_substr(minishell, name, i, ft_strlen(&name[i]) + 1);
		garbage_release(minishell, name);
	}
	return (result);
}
