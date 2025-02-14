/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:44:17 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/14 12:54:13 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void right_pipe(t_pipes *new, int pos);
static void left_pipe(t_pipes *new, int pos);
static char	*pipe_helper(t_pipes *new, int pos, int param, int param2);

/*
checks the existence of < and > 
and modifies the fd accordingly
*/

void	parse_pipe(t_pipes	*new)
{
	int		i;

	i = 0;
	while (new->content[i])
	{
		if (new->content[i] == '<')
			right_pipe(new, i);
		else if (new->content[i] == '>')
			left_pipe(new, i);
		else
			i++;
	}
}

static void	right_pipe(t_pipes *new, int pos)
{
	char	*path;

	if (new->content[pos + 1] == '<')
	{
		path = pipe_helper(new, pos, 2, 1);
		new->fd_in = fill_here_doc(new, path);
	}
	else
	{
		path = pipe_helper(new, pos, 1, 1);
		new->fd_in = open(path, O_CREAT | O_RDWR, 00400);
	}
}

static void	left_pipe(t_pipes *new, int pos)
{
	char 	*path;

	if (new->content[pos + 1] == '>')
	{
		path = pipe_helper(new, pos, 2, 2);
		new->fd_out = open(path, O_CREAT | O_APPEND | O_RDWR, 00700);
	}
	else
	{
		path = pipe_helper(new, pos, 1, 2);
		if (!access(path, F_OK))
			unlink(path);
		new->fd_out = open(path, O_CREAT | O_RDWR, 00700);
	}
}

static char	*pipe_helper(t_pipes *new, int pos, int param, int param2)
{
	int		j;
	char	**result;
	char	*path;

	j = pos + param;
	if (new->content[j] == ' ')
	{
		while (new->content[j] == ' ')
			j++;
	}
	while (new->content[j] && new->content[j] != '<' && new->content[j] != '>' && new->content[j] != ' ')
		j++;
	if (param2 == 2 && new->fd_out != STDOUT_FILENO)
		close(new->fd_out);	
	if (param2 == 1 && new->fd_in != STDIN_FILENO)
		close(new->fd_in);
	result = extract_str(new->content, pos, j);
	new->content = ft_strtrim(ft_strdup(result[0]), "< >");
	path = ft_strtrim(result[1], "< >");
	return (path);
}
