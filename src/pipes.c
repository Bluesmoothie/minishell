/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:07:02 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/11 17:10:16 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				treat_piped_element(t_pipes	*new);
static int			left_pipe(t_pipes *new, int pos);
static int			right_pipe(t_pipes *new, int pos);
static void			treat_pipe(t_minishell *minishell, t_pipes *unpiped);
static t_pipes		**create_pipe_list(char *line);
int					here_doc(t_pipes *new, char *tmp);

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
	{	
		if ((*unpiped)->fd_in != STDIN_FILENO)
			dup2((*unpiped)->fd_in, STDIN_FILENO);
		if ((*unpiped)->fd_out != STDOUT_FILENO)
			dup2((*unpiped)->fd_out, STDOUT_FILENO);		
		treat_arguments(minishell, (*unpiped)->content, STDOUT_FILENO);
	}
	else while (*unpiped)
	{
		if ((*unpiped)->fd_in != STDIN_FILENO)
			return ;
		if ((*unpiped)->fd_out != STDOUT_FILENO)
			dup2((*unpiped)->fd_out, STDOUT_FILENO);
		treat_pipe(minishell, *unpiped);
		*unpiped = (*unpiped)->next;
	}
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
}

static void	treat_pipe(t_minishell *minishell, t_pipes *unpiped)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
		return (free_exit(minishell, NULL, E_FORKFAIL));
	if (pid == 0)
	{
		if (close(pipefd[0]) == -1)
			return (free_exit(minishell, NULL, "Close failed"));
		if (unpiped->next && (dup2(pipefd[1], unpiped->fd_out) == -1))
			return (free_exit(minishell, NULL, "dup2 failed"));
		treat_arguments(minishell, unpiped->content, unpiped->fd_out);
		if (close(pipefd[1]) == -1)
			return (free_exit(minishell, NULL, "close failed"));		
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (unpiped->next && (dup2(pipefd[0], unpiped->fd_in) == -1))
			return (free_exit(minishell, NULL, "dup2 failed"));
		if (waitpid(pid, NULL, 0) == -1)
			return (free_exit(minishell, NULL, "waitpid failed"));
	}
	if (close(pipefd[1]) == -1)
		return (free_exit(minishell, NULL, "close failed"));
}
static t_pipes		**create_pipe_list(char *line)
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
			return(pipeclear(*list), NULL);
		treat_piped_element(new);
		pipeadd_back(list, new);
		i++;
	}
	return (list);
}

void	treat_piped_element(t_pipes	*new)
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
		new->fd_in = here_doc(new, tmp);
		return (pos);
	}
	j++;
	while (new->content [j] && new->content[j] != '>')
		j++;
	if (new->content[j])
		j--;
	new->fd_in = open(ft_strtrim(ft_substr(new->content, pos + 1, j - pos), "< "), O_CREAT | O_RDONLY, 00400);
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
		j++;
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
	return (pos);
}

#include "get_next_line.h"

int	here_doc(t_pipes *new, char *tmp)
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
		// dup2(pipefd[1], STDOUT_FILENO);
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

/*
TODO Chevrons : 
> if fd not empty, clear it before
*/


/*
garage-blanc0@orange.fr 
*/
