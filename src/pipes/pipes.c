/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:07:02 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/19 14:39:16 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		nopipe(t_minishell *minishell, t_pipes **unpiped);
static t_bool	oneemptypipe(char *str);
static t_pipes	**create_pipe_list(char *line);

void	unpipe(t_minishell *minishell, char *line)
{
	t_pipes	**unpiped;
	int		size;
	int		tmp_in;
	int		tmp_out;

	if (line == NULL || ft_strcmp(line, "exit") == 0)
		gcall_exit(NULL);
	if (!line[0])
		return (treat_arguments(minishell, line, STDOUT_FILENO));
	if (oneemptypipe(line))
		return (gfree(line), (void)write(2, "Syntax error\n", 13));
	tmp_in = open("/dev/tty", O_RDONLY);
	tmp_out = open("/dev/tty", O_WRONLY);
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
	close(tmp_in);
	close(tmp_out);
}

static t_pipes	**create_pipe_list(char *line)
{
	t_pipes	**list;
	t_pipes	*new;
	char	*dup;
	char	**splitted;
	int		i;

	splitted = gft_split(line, '|');
	gfree(line);
	i = 0;
	list = (t_pipes **)gmalloc(sizeof(t_pipes *));
	*list = NULL;
	while (splitted[i])
	{
		dup = gman_add(ft_strdup(splitted[i]));
		new = pipecreate(dup);
		pipeadd_back(list, new);
		if (parse_pipe(new))
			break ;
		i++;
	}
	gfree_double(splitted);
	return (list);
}

static void	nopipe(t_minishell *minishell, t_pipes **unpiped)
{
	if ((*unpiped)->fd_in != STDIN_FILENO)
		dup2((*unpiped)->fd_in, STDIN_FILENO);
	if ((*unpiped)->fd_out != STDOUT_FILENO)
		dup2((*unpiped)->fd_out, STDOUT_FILENO);
	treat_arguments(minishell, (*unpiped)->content, STDOUT_FILENO);
	if (!isatty((*unpiped)->fd_in))
			close((*unpiped)->fd_in);
	if (!isatty((*unpiped)->fd_out))
			close((*unpiped)->fd_out);
	pipeclear(unpiped);
}

static t_bool	oneemptypipe(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			j = 0;
			while (str[j])
			{
				if (j == i)
					return (1);
				if (str[j] == 32 || str[j] == '>' || str[j] == '<')
					j++;
				else
					return (0);
			}
		}
		i++;
	}
	return (0);
}
