/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:43 by ygille            #+#    #+#             */
/*   Updated: 2025/01/30 16:18:49 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **envp)
{
	init_struct(minishell, envp);
	init_signals();
	init_term();
}

void	init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	init_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

t_mlist	*init_env(char **envp)
{
	t_mlist	*env;
	char	*name;
	char	*content;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		name = extract_name(envp[i]);
		content = extract_content(envp[i]);
		env = ft_mlstadd_front(env, ft_mlstcreate(name, content));
		i++;
	}
	return (env);
}
