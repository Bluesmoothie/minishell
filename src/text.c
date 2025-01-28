/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:54:08 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 00:31:52 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_text(char *text, char format[5], char color[6])
{
	ft_putstr_fd(format, 1);
	ft_putstr_fd(color, 1);
	ft_putendl_fd(text, 1);
	ft_putstr_fd(TEXT_RESET, 1);
}

char	*calc_prompt(void)
{
	char	*user;
	char	*pwd;
	char	*prompt;

	user = getenv("USER");
	pwd = get_relative_path();
	prompt = ft_strfcat(PROMPT_LEFT_COLOR, TEXT_BOLD, FALSE, FALSE);
	prompt = ft_strfcat(prompt, user, TRUE, FALSE);
	prompt = ft_strfcat(prompt, "@minishell", TRUE, FALSE);
	prompt = ft_strfcat(prompt, PROMPT_RIGHT_COLOR, TRUE, FALSE);
	prompt = ft_strfcat(prompt, ":~", TRUE, FALSE);
	prompt = ft_strfcat(prompt, pwd, TRUE, TRUE);
	prompt = ft_strfcat(prompt, TEXT_RESET, TRUE, FALSE);
	prompt = ft_strfcat(prompt, "$ ", TRUE, FALSE);
	return (prompt);
}

char	*get_relative_path(void)
{
	char	*pwd;
	char	*home;
	char	*relative_path;
	int		i;

	pwd = getenv("PWD");
	home = getenv("HOME");
	i = 0;
	while (pwd[i] && home[i] && pwd[i] == home[i])
		i++;
	relative_path = ft_strdup(&pwd[i]);
	return (relative_path);
}
