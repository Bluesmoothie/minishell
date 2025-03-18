/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:54:08 by ygille            #+#    #+#             */
/*   Updated: 2025/03/18 15:44:32 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display a text with a specific format and color
*/
void	display_text(char *text, char format[5], char color[6], int fd)
{
	ft_putstr_fd(format, fd);
	ft_putstr_fd(color, fd);
	ft_putstr_fd(text, fd);
	ft_putstr_fd(TEXT_RESET, fd);
}

/*
** Display an error message
*/
void	display_error(char *command, char *error, char *arg)
{
	display_text(command, TEXT_ITALIC, TEXT_NULL_COLOR, STDERR_FILENO);
	display_text(error, TEXT_NULL_FORMAT, TEXT_RED, STDERR_FILENO);
	if (arg)
		display_text(arg, TEXT_ITALIC, TEXT_NULL_COLOR, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

/*
** Calculate the prompt to display
*/

#if PROMPT_COLOR

char	*calc_prompt(t_minishell minishell)
{
	char	*pwd;
	char	*prompt;

	pwd = get_relative_path(minishell.pwd, minishell.home);
	prompt = ft_strfcat(PROMPT_LEFT_COLOR, TEXT_BOLD, FALSE, FALSE);
	if (minishell.user != NULL)
	{
		prompt = ft_strfcat(prompt, minishell.user, TRUE, FALSE);
		prompt = ft_strfcat(prompt, "@", TRUE, FALSE);
	}
	prompt = ft_strfcat(prompt, "minishell", TRUE, FALSE);
	prompt = ft_strfcat(prompt, PROMPT_RIGHT_COLOR, TRUE, FALSE);
	prompt = ft_strfcat(prompt, ":", TRUE, FALSE);
	if (pwd)
	{
		prompt = ft_strfcat(prompt, pwd, TRUE, FALSE);
		gfree(pwd);
	}
	prompt = ft_strfcat(prompt, TEXT_RESET, TRUE, FALSE);
	prompt = ft_strfcat(prompt, "$ ", TRUE, FALSE);
	return (gman_add(prompt));
}
#else

char	*calc_prompt(t_minishell minishell)
{
	char	*pwd;
	char	*prompt;

	pwd = get_relative_path(minishell.pwd, minishell.home);
	prompt = NULL;
	if (minishell.user != NULL)
		prompt = ft_strfcat(minishell.user, "@", FALSE, FALSE);
	prompt = ft_strfcat(prompt, "minishell", TRUE, FALSE);
	prompt = ft_strfcat(prompt, ":", TRUE, FALSE);
	if (pwd)
	{
		prompt = ft_strfcat(prompt, pwd, TRUE, FALSE);
		gfree(pwd);
	}
	prompt = ft_strfcat(prompt, "$ ", TRUE, FALSE);
	return (gman_add(prompt));
}
#endif

/*
** Get the path relative to the home directory
*/
char	*get_relative_path(char *pwd, char *home)
{
	char	*relative_path;
	char	*tmp;
	int		i;

	if (home == NULL)
		return (gman_add(ft_strdup(pwd)));
	if (pwd == NULL)
		return (NULL);
	i = 0;
	if (!(ft_strnstr(pwd, home, ft_strlen(pwd))))
		return (gman_add(ft_strdup(pwd)));
	while (pwd[i] && home[i] && pwd[i] == home[i])
		i++;
	relative_path = ft_strdup(&pwd[i]);
	tmp = gman_add(relative_path);
	relative_path = gman_add(ft_strfcat("~", relative_path, FALSE, FALSE));
	gfree(tmp);
	return (relative_path);
}
