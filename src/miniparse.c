/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:39:29 by ygille            #+#    #+#             */
/*   Updated: 2025/02/15 13:26:16 by ygille           ###   ########.fr       */
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
			i += extract_arg(&line[i], &args, &act);
			if (line[i] != '\0' && line[i] != ' '
				&& (line[i] <= '\t' || line[i] >= '\r'))
				act->glue = TRUE;
			else
				act->glue = FALSE;
		}
	}
	search_for_env(minishell, args);
	out = rebuild_args(args);
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
int	extract_arg(char *line, t_mlist **args, t_mlist **node)
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
	*node = extract_helper(line, i, sep);
	*args = ft_mlstadd_back(*args, *node);
	return (i);
}

/*
** Recreate the **tab from the nodes
*/
char	**rebuild_args(t_mlist *args)
{
	char	**result;
	char	*tmp;
	int		i;

	result = gmalloc_double(sizeof(char *) * (ft_mlstsize(args) + 1));
	i = 0;
	while (args != NULL)
	{
		result[i] = gman_add(ft_strdup(args->content));
		while (args->glue == TRUE)
		{
			tmp = result[i];
			result[i] = gman_add(ft_strfcat(result[i], args->content,
						FALSE, FALSE));
			gfree(tmp);
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
t_mlist	*extract_helper(char *line, int i, char sep)
{
	t_mlist	*node;
	char	*content;

	content = NULL;
	if (sep == ' ')
		content = ft_substr(line, 0, i);
	else if (sep == '\'' || sep == '\"')
		content = ft_substr(line, 1, i - 2);
	gman_add(content);
	node = ft_mlstcreate(NULL, content);
	node->mask = sep;
	return (node);
}
