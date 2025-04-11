/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:10:48 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/11 15:02:14 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_pos(char *content, int j);
static int	dbl_quotes(char *content, int j);
static int	spl_quotes(char *content, int j);

char	*pipe_helper(t_pipes *new, int pos, int param)
{
	int		j;
	char	**result;
	char	*path;

	j = pos + param;
	if (is_ws(new->content[j]))
		while (is_ws(new->content[j]))
			j++;
	if (!new->content[j] || new->content[j] == '<' || new->content[j] == '>')
		return ((void)write(2, "Syntax error\n", 13), NULL);
	j = find_pos(new->content, j);
	result = extract_str(new->content, pos, j);
	new->content = gman_add(ft_strdup(result[0]));
	path = gman_add(ft_strtrim(result[1], "< >"));
	gfree_double(result);
	return (path);
}

static int	find_pos(char *content, int j)
{
	while (content[j] && content[j] != '<' && content[j] != '>'
		&& !is_ws(content[j]))
	{
		if (content[j] == '"')
			j = dbl_quotes(content, j);
		else if (content[j] == '\'')
			j = spl_quotes(content, j);
		else
			j++;
	}
	return (j);
}

static int	dbl_quotes(char *content, int j)
{
	int	k;

	j++;
	k = j;
	while (content[k])
	{
		if (content[k] == '"')
		{
			k = 0;
			break ;
		}
		k++;
	}
	if (k)
		return (j);
	while (content[j] && content[j] != '"')
		j++;
	return (j);
}

static int	spl_quotes(char *content, int j)
{
	int	k;

	j++;
	k = j;
	while (content[k])
	{
		if (content[k] == '\'')
		{
			k = 0;
			break ;
		}
		k++;
	}
	if (k)
		return (j);
	while (content[j] && content[j] != '\'')
		j++;
	return (j);
}
