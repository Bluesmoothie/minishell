/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:49:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/19 16:30:28 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc(char *tmp, int pipefd1);
// static t_bool	is_finished(char *s, char c);
// static int	has_no_quotes(char *str);

int	fill_here_doc(t_pipes *new, char *tmp)
{
	int		pipefd[2];

	// if (!has_no_quotes(tmp))
	// 	write(1, "NOQUOTE\n", 8);
	// else if (has_no_quotes(tmp) == -1)
	// 	return (write(1, "bad quotes\n", 10));
	// else
	// 	write(1, "Quoted\n", 7);
	pipe(pipefd);
	run_heredoc(tmp, pipefd[1]);
	dup2(pipefd[0], new->fd_in);
	close(pipefd[0]);
	return (pipefd[0]);
}

static void	run_heredoc(char *tmp, int pipefd1)
{
	char	*last_line;
	// char	*history;

	// history = NULL;
	while (1)
	{
		last_line = readline("heredoc >");
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
	// free(history);
}

// static int	has_no_quotes(char *str)
// {
// 	int i;
	
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 34 && is_finished(&str[i], 34))
// 			return (1);
// 		else if (str[i] == 34)
// 			return (-1);
// 		else if (str[i] == 39 && is_finished(&str[i], 39))
// 			return (1);
// 		else if (str[i] == 39)
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

// static t_bool	is_finished(char *s, char c)
// {
// 	int i;

// 	i = 1;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
/*
TODO
Handle Ctrl+C -- Ctrl+V
determine if word is quoted or not
if is quoted, not handle environment variable but word is without quotes
if not, handle env variable
*/
