/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:49:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/04 17:47:37 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc(char *tmp, int pipefd1, int quoted, t_minishell *minishell);
// static char *treat_env(char *str, t_minishell *minishell);
static t_bool	is_finished(char *s, char c);
static int	has_no_quotes(char *str);

int	fill_here_doc(t_pipes *new, char *tmp, t_minishell *minishell)
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
	dup2(pipefd[0], new->fd_in);
	close(pipefd[0]);
	return (pipefd[0]);
}

static void	run_heredoc(char *tmp, int pipefd1, int quoted, t_minishell *minishell)
{
	char	*last_line;

	(void)quoted;
	(void)minishell;
	while (1)
	{
		last_line = readline("heredoc >");
		last_line = ft_strfcat(last_line, "\n", TRUE, FALSE);
		// if (!quoted)
		// 	last_line = treat_env(last_line, minishell);
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

// static char *treat_env(char *str, t_minishell *minishell)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*name;
// 	char	*tmp;
// 	char	*result;

// 	i = 0;
// 	result = NULL;
// 	while (str[i])
// 	{
// 		if (str[i++] == '$')
// 		{
// 			j = i;
// 			while (str[j] != ' ' && str[j] != '\n' && str[j] != '$' && str[j])
// 				j++;
// 			name = gman_add(ft_substr(str, i, j - i));
// 			tmp = get_env_value(minishell, name);
// 			gfree(name);
// 			result = gman_add(ft_strfcat(result, tmp, FALSE, TRUE));
// 			i = j;
// 		}
// 	}
// 	// gfree(str);
// 	return (result);
// }


/*
TODO
Handle Ctrl+C -- Ctrl+V
determine if word is quoted or not
if is quoted, not handle environment variable but word is without quotes
if not, handle env variable
*/
