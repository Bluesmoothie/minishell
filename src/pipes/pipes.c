/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:07:02 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/14 23:46:02 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		nopipe(t_minishell *minishell, t_pipes **unpiped);
static t_pipes	**create_pipe_list(char *line);

void	unpipe(t_minishell *minishell, char *line)
{
	t_pipes	**unpiped;
	int		size;
	int		tmp_in;
	int		tmp_out;

	if (line == NULL)
		gcall_exit(NULL);
	if (!line[0])
		return (treat_arguments(minishell, line, STDOUT_FILENO));
	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	unpiped = create_pipe_list(line);
	if (pipelast(*unpiped)->issue)
		return ;
	size = pipelstsize(*unpiped);
	if (!(*unpiped)->next)
		nopipe(minishell, unpiped);
	else
		multiple_pipes(minishell, unpiped, size);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
}

static t_pipes	**create_pipe_list(char *line)
{
	t_pipes	**list;
	t_pipes	*new;
	char	**splitted;
	int		i;

	splitted = ft_split(line, '|');
	if (!splitted)
		return (NULL);
	i = 0;
	list = (t_pipes **)gmalloc(sizeof(t_pipes *));
	*list = NULL;
	while (splitted[i])
	{
		new = pipecreate(ft_strdup(splitted[i]));
		if (!new)
			return (pipeclear(*list), NULL);
		if (parse_pipe(new))
			return (pipeadd_back(list, new), list);
		pipeadd_back(list, new);
		i++;
	}
	return (list);
}

static void	nopipe(t_minishell *minishell, t_pipes **unpiped)
{
	if ((*unpiped)->fd_in != STDIN_FILENO)
		dup2((*unpiped)->fd_in, STDIN_FILENO);
	if ((*unpiped)->fd_out != STDOUT_FILENO)
		dup2((*unpiped)->fd_out, STDOUT_FILENO);
	treat_arguments(minishell, (*unpiped)->content, STDOUT_FILENO);
}
