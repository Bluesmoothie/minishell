/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:57:54 by ygille            #+#    #+#             */
/*   Updated: 2025/03/06 18:12:10 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	size_calc(char *line);
static void		fill_tab(char *line, t_bool *tab);

t_bool	*quotes_verif(char *line)
{
	t_bool	*result;
	size_t	size;
	
	result = NULL;
	size = size_calc(line);
	if (size)
		result = gmalloc(size * sizeof(t_bool));
	fill_tab(line, result);
	return (tab);
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

static void	fill_tab(char *line, t_bool *tab)
{
	size_t	scount;
	size_t	dcount;
	
	scount = 0;
	dcount = 0;
	while (*line)
	{
		if (*line == '\'')
			scount++;
		else if (*line == '\"')
			dcount++;
		else if (*line == '|')
		{
			if ((scount % 2 && ft_strchr(line, '\''))
				|| (dcount % 2 && ft_strchr(line, '\"')))
				*tab = FALSE;
			else
				*tab = TRUE;
			tab++;
		}
		line++;
	}
}
