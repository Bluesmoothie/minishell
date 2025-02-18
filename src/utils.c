/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:18:50 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/18 18:59:30 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_str(char *str, int beg, int end)
{
	char	**result;
	char	tmp;
	int		i;
	int		size;

	size = end - beg;
	result = (char **)gmalloc_double(3 * sizeof(char *));
	result[0] = gman_add(ft_strdup(str));
	result[1] = gman_add(ft_substr(str, beg, size));
	result[2] = NULL;
	i = 0;
	while (i < beg)
		i++;
	while (result[0][i + size])
	{
		tmp = result[0][i + size];
		result[0][i] = tmp;
		i++;
	}
	ft_bzero(&result[0][i], size);
	gfree(str);
	return (result);
}

char	*verif_file(char *path)
{
	t_stat	path_stat;

	if (path != NULL)
	{
		if (access(path, F_OK | X_OK) == 0)
		{
			stat(path, &path_stat);
			if (S_ISREG(path_stat.st_mode))
				return (path);
		}
	}
	free (path);
	return (NULL);
}

void	returns_process(int code, t_return *ret)
{
	if (WIFEXITED(code))
	{
		ret->exited = TRUE;
		ret->exit_stat = WEXITSTATUS(code);
	}
	else
		ret->exited = FALSE;
	ret->signaled = WIFSIGNALED(code);
	ret->termsig = WTERMSIG(code);
	ret->coredump = __WCOREDUMP(code);
	ret->stopped = WIFSTOPPED(code);
	ret->stopsig = WSTOPSIG(code);
}
