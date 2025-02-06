/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:29:21 by ygille            #+#    #+#             */
/*   Updated: 2025/02/06 15:30:42 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1 != NULL)
		while (s1[j])
			str[i++] = s1[j++];
	j = 0;
	if (s2 != NULL)
		while (s2[j])
			str[i++] = s2[j++];
	str[i] = '\0';
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (str);
}

/*
** Like strcat but can choose if a string needs to be freed
*/
char	*ft_strfcat(char *s1, char *s2, t_bool fs1, t_bool fs2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1 != NULL)
		while (s1[j])
			str[i++] = s1[j++];
	j = 0;
	if (s2 != NULL)
		while (s2[j])
			str[i++] = s2[j++];
	str[i] = '\0';
	if (fs1 && s1 != NULL)
		free(s1);
	if (fs2 && s2 != NULL)
		free(s2);
	return (str);
}

void	free_split(char ***split)
{
	int	i;

	i = 0;
	if (*split == NULL)
		return ;
	while ((*split)[i])
		free((*split)[i++]);
	free(*split);
	*split = NULL;
}
