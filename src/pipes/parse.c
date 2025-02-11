/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:44:17 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/11 19:13:03 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	right_pipe(t_pipes *new, int pos);
static int	left_pipe(t_pipes *new, int pos);
static int	fill_here_doc(t_pipes *new, char *tmp);
static void	left_pipe_helper(t_pipes *new, int pos);

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
			i = right_pipe(new, i);
		if (new->content[i] == '>')
			i = left_pipe(new, i);
		i++;
	}
	i = 0;
	while (new->content[i])
	{
		if (new->content[i] == '<' || new->content[i] == '>')
			break;
		i++;
	}
	ft_bzero(&new->content[i], ft_strlen(new->content) - i);
}

static int	right_pipe(t_pipes *new, int pos)
{
	int		j;
	char	*tmp;

	j = pos;
	if (new->content[pos + 1] == '<')
	{
		pos += 2;
		j = pos;
		while (new->content [j] && new->content[j] != '>' && new->content[j] != '<')
			j++;
		if (new->content[j])
			j--;
		tmp = ft_strtrim(ft_substr(new->content, pos + 1, j - pos), "< >");
		new->fd_in = fill_here_doc(new, tmp);
		return (j);
	}
	j = pos++;
	while (new->content [j] && new->content[j] != '>')
		j++;
	if (new->content[j])
		j--;
	new->fd_in = open(ft_strtrim(ft_substr(new->content, pos + 1, j - pos), "< "), O_CREAT | O_RDWR, 00400);
	return (pos);
}

static int	left_pipe(t_pipes *new, int pos)
{
	int 	j;

	j = pos;
	if (new->content[pos + 1] == '>')
	{
		pos++;
		j++;
		if (new->fd_out != STDOUT_FILENO)
			close(new->fd_out);
		while (new->content [j] && new->content[j] != '<' && new->content[j] != '>')
			j++;
		if (new->content[j])
			j--;
		new->fd_out = open(ft_strtrim(ft_substr(new->content, pos + 1, j - pos), " >"), O_CREAT | O_APPEND | O_RDWR, 00700);
	}	
	else
	{
		left_pipe_helper(new, pos++);
	}
	return (pos);
}

static void	left_pipe_helper(t_pipes *new, int pos)
{
	int		j;
	
	j = pos++;
	while (new->content [j] && new->content[j] != '<' && new->content[j] != '>')
		j++;
	if (new->content[j])
		j--;
	if (new->fd_out != STDOUT_FILENO)
		close(new->fd_out);
	if (!access(ft_strtrim(ft_substr(new->content, pos + 1, j - pos), " >"), F_OK))
		unlink(ft_strtrim(ft_substr(new->content, pos + 1, j - pos), " >"));
	new->fd_out = open(ft_strtrim(ft_substr(new->content, pos + 1, j - pos), " >"), O_CREAT | O_RDWR, 00700);
}

static int	fill_here_doc(t_pipes *new, char *tmp)
{
	int		pipefd[2];
	int		pid;
	char	*last_line;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (close(pipefd[0]) == -1)
			return (-1) ;
		while (1)
		{
			write(STDOUT_FILENO, "heredoc >", 9);
			last_line = get_next_line(STDIN_FILENO);
			if (!ft_strncmp(last_line, tmp, ft_strlen(tmp)))
			{	
				close(pipefd[1]);
				break ;
			}
			write(pipefd[1], last_line, ft_strlen(last_line));
			free(last_line);
		}
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipefd[0], new->fd_in);
		close(pipefd[0]);
	}
	return(pipefd[0]);
}
