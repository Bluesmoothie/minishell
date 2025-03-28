/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:25:18 by ygille            #+#    #+#             */
/*   Updated: 2025/03/10 14:59:33 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	size_calc(char *line);
static void		fill_tab(char *line, t_bool *tab);

t_bool	*quotes_verif_chevron(char *line)
{
	t_bool	*result;
	size_t	size;

	result = NULL;
	size = size_calc(line);
	result = gmalloc(size * sizeof(t_bool));
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
		if (line[pos] == '<' || line[pos] == '>')
			size++;
		pos++;
	}
	return (size);
}

static void	fill_tab(char *line, t_bool *tab)
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
		else if (line[pos] == '<' || line[pos] == '>')
		{
			if (!((scount % 2 && ft_strchr(&line[pos], '\''))
					|| (dcount % 2 && ft_strchr(&line[pos], '\"'))))
				*tab = TRUE;
			else
				*tab = FALSE;
			tab++;
		}
		pos++;
	}
}
