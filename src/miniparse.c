/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:39:29 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 16:13:58 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Hormone boosted parsing
*/
char	**miniparse(t_minishell *minishell, char *line)
{
	t_mlist	*args;
	t_mlist	*act;
	char	**out;
	int		i;

	i = 0;
	args = NULL;
	while (line[i] != '\0')
	{
		i += skip_whitespaces(&line[i]);
		if (line[i] != '\0')
		{
			i += extract_arg(minishell, &line[i], &args, &act);
			if (line[i] != '\0' && line[i] != ' '
				&& (line[i] <= '\t' || line[i] >= '\r'))
				act->glue = TRUE;
			else
				act->glue = FALSE;
		}
	}
	search_for_env(minishell, args);
	out = rebuild_args(minishell, args);
	ft_mlstclear(args);
	return (out);
}

/*
** Skip whitespaces
** just like the name
** no secrets here
*/
int	skip_whitespaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
		i++;
	return (i);
}

/*
** Create a node with an arg
*/
int	extract_arg(t_minishell *minishell, char *line,
	t_mlist **args, t_mlist **node)
{
	int		i;
	char	sep;

	i = 1;
	if (line[0] == '\"' && ft_strchr(&line[1], '\"') != NULL)
		sep = '\"';
	else if (line[0] == '\'' && ft_strchr(&line[1], '\'') != NULL)
		sep = '\'';
	else
		sep = ' ';
	while (line[i] != '\0' && line[i] != sep
		&& line[i] != '\"' && line[i] != '\'')
		i++;
	if (sep != ' ' && line[i] == sep)
		i++;
	*node = extract_helper(minishell, line, i, sep);
	*args = ft_mlstadd_back(*args, *node);
	return (i);
}

/*
** Recreate the **tab from the nodes
*/
char	**rebuild_args(t_minishell *minishell, t_mlist *args)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (ft_mlstsize(args) + 1));
	if (result == NULL)
		free_exit(minishell, E_MALLOC);
	i = 0;
	while (args != NULL)
	{
		result[i] = ft_strdup(args->content);
		if (result[i] == NULL)
			free_exit(minishell, E_MALLOC);
		while (args->glue == TRUE)
		{
			result[i] = ft_strfcat(result[i], args->content, TRUE, FALSE);
			if (result[i] == NULL)
				free_exit(minishell, E_MALLOC);
			args = args->next;
		}
		args = args->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

/*
** Extract the exact portion needed for
** extract_arg
*/
t_mlist	*extract_helper(t_minishell *minishell, char *line, int i, char sep)
{
	t_mlist	*node;
	char	*content;

	content = NULL;
	if (sep == ' ')
		content = ft_substr(line, 0, i);
	else if (sep == '\'' || sep == '\"')
		content = ft_substr(line, 1, i - 2);
	if (content == NULL)
		free_exit(minishell, E_MALLOC);
	node = ft_mlstcreate(NULL, content);
	if (node == NULL)
		free_exit(minishell, E_MALLOC);
	node->mask = sep;
	return (node);
}
