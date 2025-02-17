/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:43 by ygille            #+#    #+#             */
/*   Updated: 2025/02/17 19:59:03 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Launch all initializations
*/
void	init_minishell(t_minishell *minishell, char **envp)
{
	init_struct(minishell, envp);
	init_signals();
	init_term();
}

/*
** Initialize signals handling
*/
void	init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

/*
** Initialize terminal parameters
*/
void	init_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term_param_restore(term, 0);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/*
** Initialize the environment variables
*/
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

void	term_param_restore(struct termios param, t_bool restore)
{
	static struct termios	param_mem;

	if (!restore)
		param_mem = param;
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &param_mem);
}
