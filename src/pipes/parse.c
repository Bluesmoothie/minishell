/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:44:17 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/15 17:51:25 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int right_pipe(t_pipes *new, int pos);
static int left_pipe(t_pipes *new, int pos);
static char	*pipe_helper(t_pipes *new, int pos, int param, int param2);

/*
checks the existence of < and > 
and modifies the fd accordingly
*/

int	parse_pipe(t_pipes	*new)
{
	int		i;
	int 	j;

	i = 0;
	while (new->content[i])
	{
		j = 0;
		if (new->content[i] == '<')
			j = right_pipe(new, i);
		else if (new->content[i] == '>')
			j = left_pipe(new, i);
		if (j)
		{	
			gfree(new->content);
			new->issue = 1;
			return (1);
		}
		i ++;
	}
	return (0);
}

static int	right_pipe(t_pipes *new, int pos)
{
	char	*path;

	if (new->content[pos + 1] == '<')
	{
		if (new->content[pos + 2] == '<' || new->content[pos + 2] == '>')
			return (write(2, "Syntax error\n", 13));
		path = pipe_helper(new, pos, 2, 1);
		if (!path)
			return (1);
		new->fd_in = fill_here_doc(new, path);
	}
	else
	{
		path = pipe_helper(new, pos, 1, 1);
		if (!path)
			return (1);
		if (access(path, F_OK))
			return (printf("%s: No such file or directory\n", path));
		if (access(path, R_OK))
			return (printf("%s: permission denied\n", path));
		new->fd_in = open(path, O_RDONLY, 00400);
	}
	return (0);
}

static int	left_pipe(t_pipes *new, int pos)
{
	char 	*path;

	if (new->content[pos + 1] == '>')
	{
		if (new->content[pos + 2] == '<' || new->content[pos + 2] == '>')
			return (write(2, "Syntax error\n", 13));
		path = pipe_helper(new, pos, 2, 2);
		if (!path)
			return (1);
		new->fd_out = open(path, O_CREAT | O_APPEND | O_RDWR, 00700);
	}
	else
	{
		path = pipe_helper(new, pos, 1, 2);
		if (!path)
			return (1);
		if (!access(path, F_OK))
			unlink(path);
		new->fd_out = open(path, O_CREAT | O_RDWR, 00700);
	}
	return (0);
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
	if (!new->content[j] || new->content[j] == '<' || new->content[j] == '>')
		return ((void)write(2, "Syntax error\n", 13), NULL);
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
