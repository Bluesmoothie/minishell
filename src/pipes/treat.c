/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:49:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/05 19:13:30 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc(char *tmp, int pipefd1, int quoted, t_minishell *minishell);
static t_bool	is_finished(char *s, char c);
static int	has_no_quotes(char *str);

void	fill_here_doc(t_pipes *new, char *tmp, t_minishell *minishell)
{
	int		pipefd[2];
	int		quoted;
 
	quoted = 1;
	if (!has_no_quotes(tmp))
		quoted = 0;
	else if (has_no_quotes(tmp) == -1)
		gcall_exit("Close your quotes!\n");
	else
		tmp = gman_add(trimndelete(tmp, " \"\'"));
	pipe(pipefd);
	run_heredoc(tmp, pipefd[1], quoted, minishell);
	new->fd_in = dup(pipefd[0]);
	close(pipefd[0]);
	if (new->fd_in == -1)
		gcall_exit(E_DUP);
}

static void	run_heredoc(char *tmp, int pipefd1, int quoted, t_minishell *minishell)
{
	char	*last_line;

	while (1)
	{
		(void)quoted;
		(void)minishell;
		last_line = readline("heredoc >");
		if (!quoted)
			last_line = treat_env(last_line, minishell);
		last_line = ft_strfcat(last_line, "\n", TRUE, FALSE);
		// history = ft_strfcat(history, last_line, TRUE, FALSE);
		if (!ft_strncmp(last_line, tmp, ft_strlen(tmp)))
		{
			close(pipefd1);
			// add_history(history);
			// free(history);
			free(last_line);
			return ;
		}
		write(pipefd1, last_line, ft_strlen(last_line));
		free(last_line);
	}
}

static int	has_no_quotes(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 && is_finished(&str[i], 34))
			return (1);
		else if (str[i] == 34)
			return (-1);
		else if (str[i] == 39 && is_finished(&str[i], 39))
			return (1);
		else if (str[i] == 39)
			return (-1);
		i++;
	}
	return (0);
}

static t_bool	is_finished(char *s, char c)
{
	int i;

	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}




/*
Parcourir la str.
Des qu'on trouve un $, go jusqu'au separateur (32, 9->13, " ' \)
on met dans liste chainée 


*/

/*
TODO
Handle Ctrl+C -- Ctrl+V
determine if word is quoted or not
if is quoted, not handle environment variable but word is without quotes
if not, handle env variable
*/


/*
typedef struct s_mlist
{
	char	mask; --> SPACE
	char	*name; --> NULL
	char	*content; -->line
	t_bool	glue; --> FALSE
	t_mlist	*next;
}	t_mlist;
*/