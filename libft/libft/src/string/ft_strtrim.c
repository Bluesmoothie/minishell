/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:15:13 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:32:40 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

static	size_t	find_start(char const *s1, char const *set);
static	size_t	find_end(char const *s1, char const *set);

/*
** Return a new string copying s1 truncating the characters of set
** at the start and the end
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	size_t	start;
	size_t	end;
	char	*trim;

	start = find_start(s1, set);
	end = find_end(s1, set);
	if (start == ft_strlen(s1))
		size = 1;
	else
		size = end - start + 2;
	trim = malloc (sizeof(char) * size);
	if (trim == NULL)
		return (trim);
	if (start == ft_strlen(s1))
		trim[0] = '\0';
	else
		ft_strlcpy(trim, &s1[start], size);
	return (trim);
}

static	size_t	find_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(set) == 0)
		return (0);
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0' && set[j] != s1[i])
			j++;
		if (set[j] == s1[i])
			i++;
		else
			return (i);
	}
	return (i);
}

static	size_t	find_end(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		return (0);
	if (ft_strlen(set) == 0)
		return (i);
	while (i != 0)
	{
		j = 0;
		while (set[j] != '\0' && set[j] != s1[i])
			j++;
		if (set[j] == s1[i])
			i--;
		else
			return (i);
	}
	return (i);
}
