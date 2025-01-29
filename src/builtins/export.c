/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:06 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 19:44:31 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	func_export(t_minishell *minishell, char **args)
{
	t_mlist	*new;
	char	*name;
	char	*content;

	content = NULL;
	if (args[1] == NULL)
		return (func_env(minishell));
	else if (ft_strchr(args[1], '=') == NULL)
		name = args[1];
	else
	{
		name = extract_name(args[1]);
		content = extract_content(args[1]);
	}
	new = ft_mlstcreate(name, content);
	if (new == NULL)
		free_exit(minishell, args, E_MALLOCFAIL);
	minishell->env = ft_mlstadd_front(minishell->env, new);
	return (0);
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
