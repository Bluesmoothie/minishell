/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:06 by ygille            #+#    #+#             */
/*   Updated: 2025/02/18 18:59:13 by ygille           ###   ########.fr       */
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
		return (func_env(minishell, fd, 1));
	else if (ft_strchr(args[1], '=') == NULL)
		name = gman_add(ft_strdup(args[1]));
	else
	{
		name = extract_name(args[1]);
		content = extract_content(args[1]);
	}
	if (!ft_mlstsearch(minishell->env, name) && name[0] != '\0')
	{
		new = ft_mlstcreate(name, content);
		minishell->env = ft_mlstadd_front(minishell->env, new);
	}
	else if (name[0] != '\0')
		replace_env(minishell, name, content);
	return (0);
}

/*
Creates the accurate environment variable
*/

// t_mlist *ft_envcreate(char *name, char *content)
// {
// 	if (content)
// 		return (ft_mlstcreate(name, content));
// }

/*
** Replace a env if it exist
*/
void	replace_env(t_minishell *minishell, char *name, char *content)
{
	t_mlist	*target;

	target = ft_mlstsearch(minishell->env, name);
	gfree(target->content);
	target->content = content;
}

/*
** Return the left side of name=content
*/
char	*extract_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_substr(arg, 0, i);
	return (gman_add(name));
}

/*
** Return the right side of name=content
*/
char	*extract_content(char *arg)
{
	int		i;
	char	*content;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
		return (NULL);
	content = ft_strdup(&arg[i + 1]);
	return (gman_add(content));
}
