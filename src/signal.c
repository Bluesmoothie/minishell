/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:33:55 by ygille            #+#    #+#             */
/*   Updated: 2025/02/16 13:55:12 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler_helper(t_minishell *minishell, int sig, t_bool call);
static void	local_signal(int sig);

/*
** Pass the struct pointer to signal_handler
*/
void	siginit_struct(t_minishell *minishell)
{
	signal_handler_helper(minishell, 0, FALSE);
}

/*
** Signal handler for SIGINT and SIGQUIT
*/
void	signal_handler(int sig)
{
	signal_handler_helper(NULL, sig, TRUE);
}

static void	signal_handler_helper(t_minishell *minishell, int sig, t_bool call)
{
	static t_minishell *minishell_mem = NULL;

	if (!call)
		minishell_mem = minishell;
	else if (!minishell_mem->child_pid)
		local_signal(sig);
}

static void	local_signal(int sig)
{
	if (sig == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		if (sig == SIGQUIT)
		{
			rl_on_new_line();
			rl_redisplay();
		}
}
