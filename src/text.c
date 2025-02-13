/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:54:08 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 17:40:38 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display a text with a specific format and color
*/
void	display_text(char *text, char format[5], char color[6])
{
	ft_putstr_fd(format, 1);
	ft_putstr_fd(color, 1);
	ft_putstr_fd(text, 1);
	ft_putstr_fd(TEXT_RESET, 1);
}

/*
** Display an error message
*/
void	display_error(char *command, char *error, char *arg)
{
	display_text(command, TEXT_ITALIC, TEXT_NULL_COLOR);
	display_text(error, TEXT_NULL_FORMAT, TEXT_RED);
	if (arg)
		display_text(arg, TEXT_ITALIC, TEXT_NULL_COLOR);
	ft_putchar_fd('\n', 1);
}

/*
** Calculate the prompt to display
*/
char	*calc_prompt(t_minishell minishell)
{
	char	*pwd;
	char	*prompt;

	pwd = get_relative_path(&minishell, minishell.pwd, minishell.home);
	prompt = garbage_strfcat(&minishell, PROMPT_LEFT_COLOR, TEXT_BOLD, 0);
	prompt = garbage_strfcat(&minishell, prompt, minishell.user, 10);
	prompt = garbage_strfcat(&minishell, prompt, "@minishell", 10);
	prompt = garbage_strfcat(&minishell, prompt, PROMPT_RIGHT_COLOR, 10);
	prompt = garbage_strfcat(&minishell, prompt, ":", 10);
	prompt = garbage_strfcat(&minishell, prompt, pwd, 11);
	prompt = garbage_strfcat(&minishell, prompt, TEXT_RESET, 10);
	prompt = garbage_strfcat(&minishell, prompt, "$ ", 10);
	return (prompt);
}

/*
** Get the path relative to the home directory
*/
char	*get_relative_path(t_minishell *minishell, char *pwd, char *home)
{
	char	*relative_path;
	int		i;

	i = 0;
	if (!(ft_strnstr(pwd, home, ft_strlen(pwd))))
		return (pwd);
	while (pwd[i] && home[i] && pwd[i] == home[i])
		i++;
	relative_path = garbage_strdup(minishell, &pwd[i]);
	relative_path = garbage_strfcat(minishell, "~", relative_path, 1);
	return (relative_path);
}
