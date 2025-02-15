/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:13:22 by ygille            #+#    #+#             */
/*   Updated: 2025/02/15 13:08:44 by ygille           ###   ########.fr       */
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
				env_name = get_env_name(&start[1]);
				val = get_env_value(minishell, env_name);
				replace_env_value(args, val);
				start = ft_strchr(args->name, '$');
			}
			gfree (args->name);
			start = NULL;
			val = NULL;
		}
		args = args->next;
	}
}

/*
** Return the frist found env name from the passed arg
*/
char	*get_env_name(char *arg)
{
	int		i;
	char	*result;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '$')
		i++;
	result = gmalloc(sizeof(char) * i);
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
		return (gman_add(ft_itoa(minishell->last_return_value)));
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
void	replace_env_value(t_mlist *node, char *value)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	while (node->name[i] != '$')
		i++;
	if (i > 0)
	{
		result = ft_substr(node->name, 0, i);
		tmp = gman_add(result);
		result = ft_strfcat(result, value, FALSE, FALSE);
		gfree(tmp);
	}
	else
		result = ft_strdup(value);
	gman_add(result);
	node->content = gman_add(ft_strjoin(node->content, result));
	gfree(result);
	node->name = update_searching(node->name, i + 1);
}

/*
** Update name to permit others env var to be found
*/
char	*update_searching(char *name, int i)
{
	char	*result;

	result = NULL;
	while (name[i] != '\0' && name[i] != '$')
		i++;
	if (name[i] == '\0')
		gfree(name);
	else
	{
		result = ft_substr(name, i, ft_strlen(&name[i]) + 1);
		gfree(name);
	}
	return (gman_add(result));
}
