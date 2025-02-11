/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:06 by ygille            #+#    #+#             */
/*   Updated: 2025/02/11 14:11:48 by ygille           ###   ########.fr       */
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
		name = extract_name(args[1]);
		content = extract_content(args[1]);
	}
	if (!ft_mlstsearch(minishell->env, name))
	{
		new = ft_mlstcreate(name, content);
		if (new == NULL)
			free_exit(minishell, args, E_MALLOCFAIL);
		minishell->env = ft_mlstadd_front(minishell->env, new);
	}
	else
		replace_env(minishell, name, content);
	return (0);
}

void	replace_env(t_minishell *minishell, char *name, char *content)
{
	t_mlist	*target;

	target = ft_mlstsearch(minishell->env, name);
	if (target->content)
		free(target->content);
	target->content = content;
}

char	*extract_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_substr(arg, 0, i);
	return (name);
}

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
	return (content);
}
