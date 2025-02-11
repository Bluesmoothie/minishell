/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:07:02 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/11 18:20:30 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			treat_piped_element(t_pipes *new);
static t_pipes	**create_pipe_list(char *line);
static void		multiple_pipes(t_minishell *minishell, t_pipes *unpiped);
static void		nopipe(t_minishell *minishell, t_pipes **unpiped);

/*
Split line with pipes
creates children and executes commands inside
*/

void	unpipe(t_minishell *minishell, char *line)
{
	t_pipes	**unpiped;
	int		tmp_in;
	int		tmp_out;

	if (line == NULL)
		free_exit(minishell, NULL, NULL);
	if (!line[0])
		return (treat_arguments(minishell, line, STDOUT_FILENO));
	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	unpiped = create_pipe_list(line);
	if (!unpiped)
		free_exit(minishell, NULL, E_SPLITFAIL);
	if (!(*unpiped)->next)
		nopipe(minishell, unpiped);
	else
	{
		while (*unpiped)
		{
			multiple_pipes(minishell, *unpiped);
			*unpiped = (*unpiped)->next;
		}
	}
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
	list = (t_pipes **)malloc(sizeof(t_pipes *));
	*list = NULL;
	if (!list)
		return (NULL);
	while (splitted[i])
	{
		new = pipecreate(splitted[i]);
		if (!new)
			return (pipeclear(*list), NULL);
		parse_pipe(new);
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

static void	multiple_pipes(t_minishell *minishell, t_pipes *unpiped)
{
	if (unpiped->fd_in != STDIN_FILENO)
		return ;
	if (unpiped->fd_out != STDOUT_FILENO)
		dup2(unpiped->fd_out, STDOUT_FILENO);
	treat_pipe(minishell, unpiped);
}
