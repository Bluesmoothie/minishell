/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:07:02 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/18 18:24:34 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		nopipe(t_minishell *minishell, t_pipes **unpiped);
static t_bool	oneemptypipe(char *str);
static t_pipes	**create_pipe_list(char *line, t_minishell *minishell, int *p);
static void		reinit_fds(void);

void	unpipe(t_minishell *minishell, char *line, int *pos)
{
	t_pipes	**unpiped;
	int		size;

	if (line == NULL || ft_strcmp(line, "exit") == 0)
		gcall_exit(NULL);
	if (!line[0])
		return (treat_arguments(minishell, line));
	if (oneemptypipe(line))
		return (gfree(line), (void)write(2, "Syntax error\n", 13));
	unpiped = create_pipe_list(line, minishell, pos);
	if (pipelast(*unpiped)->issue)
		return ;
	size = pipelstsize(*unpiped);
	if (!(*unpiped)->next)
		nopipe(minishell, unpiped);
	else
		multiple_pipes(minishell, unpiped, size);
	reinit_fds();
}

static t_pipes	**create_pipe_list(char *line, t_minishell *minishell, int *pos)
{
	t_pipes	**list;
	t_pipes	*new;
	char	*dup;
	char	**splitted;
	int		i;

	splitted = split_quotes(line, pos);
	gfree(line);
	i = 0;
	list = (t_pipes **)gmalloc(sizeof(t_pipes *));
	*list = NULL;
	while (splitted[i])
	{
		dup = gman_add(ft_strdup(splitted[i]));
		new = pipecreate(dup);
		pipeadd_back(list, new);
		if (parse_pipe(new, minishell))
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
	treat_arguments(minishell, (*unpiped)->content);
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

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			j = i + 1;
			while (str[j] && ((str[j] == 32 || str[j] == '>' || str[j] == '<') \
			|| (str[j] > 9 && str[j] < 13)))
				j++;
			if (str[j] == '|' || str[j] == '\0')
				return (1);
		}
	}
	return (0);
}

static void	reinit_fds(void)
{
	int	tmp_in;
	int	tmp_out;

	tmp_in = open("/dev/tty", O_RDONLY);
	tmp_out = open("/dev/tty", O_WRONLY);
	if (tmp_in == -1 || tmp_out == -1)
		return (gcall_exit(E_OPEN));
	if (dup2(tmp_in, STDIN_FILENO) == -1)
		gcall_exit(E_DUP2);
	if (dup2(tmp_out, STDOUT_FILENO) == -1)
		gcall_exit(E_DUP2);
	if (close(tmp_in) == -1)
		gcall_exit(E_CLOSE);
	if (close(tmp_out) == -1)
		gcall_exit(E_CLOSE);
}
