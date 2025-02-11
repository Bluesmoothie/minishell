/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:07:02 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/11 09:08:05 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			treat_pipe(t_minishell *minishell, t_pipes *unpiped);
static t_pipes		**create_pipe_list(char *line);

/*
Split line with pipes
creates children and executes commands inside
*/

void	unpipe(t_minishell *minishell, char *line)
{
	t_pipes	**unpiped;
	int		in;
	int		i;

	if (line == NULL)
		free_exit(minishell, NULL, NULL);
	unpiped = create_pipe_list(line);
	if (!unpiped)
		free_exit(minishell, NULL, E_SPLITFAIL);
	in = dup(STDIN_FILENO);
	i = 0;
	while (*unpiped)
	{	
		treat_pipe(minishell, *unpiped);
		*unpiped = (*unpiped)->next;
	}
	dup2(in, STDIN_FILENO);
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
		if (unpiped->next && (dup2(pipefd[1], STDOUT_FILENO) == -1))
			return (free_exit(minishell, NULL, "dup2 failed"));
		treat_arguments(minishell, unpiped->content, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (unpiped->next && (dup2(pipefd[0], STDIN_FILENO) == -1))
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
		pipeadd_back(list, new);
		i++;
	}
	return (list);
}

// void	treat_piped_element(t_pipes	*new)
// {
// 	int		i;
// 	int		j;
// 	char	*first;
// 	char	*second;

// 	i = 0;
// 	while (new->content[i])
// 	{
// 		if (new->content[i] == '<' || new->content[i] == '>')
// 		{
// 			first = ft_substr(new->content, i, ft_strlen(new->content) - i);
// 			if (!first)
// 				return ;
// 			ft_bzero(new->content + i, ft_strlen(new->content) - i);
// 		}
// 		i++;
// 	}
// }

/*
How I will do --> 
When I have a pipe, I split
then I do all the checks to put all the pipes inside a struct
and I perform the redirection depending on the pipes




CASES
< -->
	< --> 
		\0 BREAK
		> -->
			\0	



< then >> 
<< then > 
<< then >> 

> then < 
> then >> 
>> then <
>> then <<

garage-blanc0@orange.fr 
*/
