/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:43:26 by ygille            #+#    #+#             */
/*   Updated: 2025/02/18 13:44:29 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

static size_t	count_words(char const *s, char c);
static size_t	fill(char *line, size_t i, char c, char const *s);
static size_t	line_size(size_t i, char c, char const *s);

/*
** Return an array of strings
** each line contain a word from s seperated with c
** terminated by NULL
*/
char	**gft_split(char const *s, char c)
{
	char	**tab;
	size_t	words;
	size_t	i;
	size_t	j;

	words = count_words(s, c);
	tab = gmalloc(sizeof(char *) * (words + 1));
	i = 0;
	j = 0;
	while (i < words)
	{
		tab[i] = gmalloc (sizeof(char) * (line_size(j, c, s)) + 1);
		j = fill(tab[i++], j, c, s);
	}
	tab[i] = NULL;
	return (tab);
}

static	size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	j = 0;
	if (c == 0 && s[i] != '\0')
		return (1);
	if (c == 0 && s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		i += j;
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
		if (j)
			count++;
	}
	return (count);
}

static	size_t	fill(char *line, size_t i, char c, char const *s)
{
	size_t	j;

	j = 0;
	while (s[i] == c)
		i++;
	while (s[i + j] != '\0' && s[i + j] != c)
	{
		line[j] = s[i + j];
		j++;
	}
	line[j] = '\0';
	return (i + j);
}

static	size_t	line_size(size_t i, char c, char const *s)
{
	size_t	size;

	size = 0;
	while (s[i] == c)
		i++;
	while (s[i + size] != c && s[i + size] != '\0')
		size++;
	return (size);
}
