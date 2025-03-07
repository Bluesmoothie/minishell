/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:57:54 by ygille            #+#    #+#             */
/*   Updated: 2025/03/07 16:29:14 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	size_calc(char *line);
static void		fill_tab(char *line, int *tab);

int	*quotes_verif(char *line)
{
	int		*result;
	size_t	size;

	result = NULL;
	size = size_calc(line);
	result = gmalloc((size + 1) * sizeof(int));
	fill_tab(line, result);
	return (result);
}

static size_t	size_calc(char *line)
{
	size_t	size;
	size_t	pos;

	size = 0;
	pos = 0;
	while (line[pos])
	{
		if (line[pos] == '|')
			size++;
		pos++;
	}
	return (size);
}

static void	fill_tab(char *line, int *tab)
{
	size_t	scount;
	size_t	dcount;
	size_t	pos;

	scount = 0;
	dcount = 0;
	pos = 0;
	while (line[pos])
	{
		if (line[pos] == '\'')
			scount++;
		else if (line[pos] == '\"')
			dcount++;
		else if (line[pos] == '|')
		{
			if (!((scount % 2 && ft_strchr(&line[pos], '\''))
					|| (dcount % 2 && ft_strchr(&line[pos], '\"'))))
			{
				*tab = pos;
				tab++;
			}
		}
		pos++;
	}
	*tab = -1;
}
