/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:07:43 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/06 19:21:07 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*zeropipe(int *pos, int i, char *line, int start);

char	**split_quotes(char *line, int *pos)
{
	char	**result;
	int		size;
	int		i;
	int		start;

	size = 0;
	while (pos[size] != -1)
		size++;
	size++;
	result = (char **)gmalloc((size + 1) * sizeof(char *));
	if (size == 1)
	{
		result[0] = gman_add(ft_strdup(line));
		result[1] = NULL;
		return (result);
	}
	i = -1;
	start = 0;
	while (++i < size)
	{
		result[i] = zeropipe(pos, i, line, start);
		start = pos[i] + 1;
	}
	result[i] = NULL;
	return (result);
}

static char	*zeropipe(int *pos, int i, char *line, int start)
{
	char	*result;

	if (pos[i] != -1)
		result = gman_add(ft_substr(line, start, pos[i] - start));
	else
		result = gman_add(ft_substr(line, start, ft_strlen(line) - start));
	return (result);
}
