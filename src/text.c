/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:54:08 by ygille            #+#    #+#             */
/*   Updated: 2025/02/15 18:20:04 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display a text with a specific format and color
*/
void	display_text(char *text, char format[5], char color[6])
{
	ft_putstr_fd(format, 2);
	ft_putstr_fd(color, 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd(TEXT_RESET, 2);
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
	ft_putchar_fd('\n', 2);
}

/*
** Calculate the prompt to display
*/
char	*calc_prompt(t_minishell minishell)
{
	char	*pwd;
	char	*prompt;

	pwd = get_relative_path(minishell.pwd, minishell.home);
	prompt = ft_strfcat(PROMPT_LEFT_COLOR, TEXT_BOLD, FALSE, FALSE);
	prompt = ft_strfcat(prompt, minishell.user, TRUE, FALSE);
	prompt = ft_strfcat(prompt, "@minishell", TRUE, FALSE);
	prompt = ft_strfcat(prompt, PROMPT_RIGHT_COLOR, TRUE, FALSE);
	prompt = ft_strfcat(prompt, ":", TRUE, FALSE);
	prompt = ft_strfcat(prompt, pwd, TRUE, FALSE);
	gfree(pwd);
	prompt = ft_strfcat(prompt, TEXT_RESET, TRUE, FALSE);
	prompt = ft_strfcat(prompt, "$ ", TRUE, FALSE);
	return (gman_add(prompt));
}

/*
** Get the path relative to the home directory
*/
char	*get_relative_path(char *pwd, char *home)
{
	char	*relative_path;
	char	*tmp;
	int		i;

	i = 0;
	if (!(ft_strnstr(pwd, home, ft_strlen(pwd))))
		return (pwd);
	while (pwd[i] && home[i] && pwd[i] == home[i])
		i++;
	relative_path = ft_strdup(&pwd[i]);
	tmp = gman_add(relative_path);
	relative_path = gman_add(ft_strfcat("~", relative_path, FALSE, FALSE));
	gfree(tmp);
	return (relative_path);
}
