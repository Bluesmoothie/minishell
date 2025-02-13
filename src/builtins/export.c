/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:06 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 17:41:10 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like the export command, display the environment variables
** or add a new one
*/
int	func_export(t_minishell *minishell, char **args, int fd)
{
	t_mlist	*new;
	char	*name;
	char	*content;

	content = NULL;
	if (args[1] == NULL)
		return (func_env(minishell, fd));
	else if (ft_strchr(args[1], '=') == NULL)
		name = args[1];
	else
	{
		name = extract_name(minishell, args[1]);
		content = extract_content(minishell, args[1]);
	}
	if (!ft_mlstsearch(minishell->env, name) && name[0] != '\0')
	{
		new = ft_mlstcreate(minishell, name, content);
		minishell->env = ft_mlstadd_front(minishell->env, new);
	}
	else if (name[0] != '\0')
		replace_env(minishell, name, content);
	return (0);
}

/*
** Replace a env if it exist
*/
void	replace_env(t_minishell *minishell, char *name, char *content)
{
	t_mlist	*target;

	target = ft_mlstsearch(minishell->env, name);
	if (target->content)
		garbage_release(minishell, target->content);
	target->content = content;
}

/*
** Return the left side of name=content
*/
char	*extract_name(t_minishell *minishell, char *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = garbage_substr(minishell, arg, 0, i);
	return (name);
}

/*
** Return the right side of name=content
*/
char	*extract_content(t_minishell *minishell, char *arg)
{
	int		i;
	char	*content;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
		return (NULL);
	content = garbage_strdup(minishell, &arg[i + 1]);
	return (content);
}
