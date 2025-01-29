/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:41 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 18:59:13 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int			pid;
	char		**null_argv;
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	null_argv = (char *[]){"", NULL};
	pid = fork();
	if (pid == -1)
		error("fork failed");
	if (pid == 0)
		execve("/bin/clear", null_argv, envp);
	if (waitpid(pid, NULL, 0) == -1)
		error("waitpid failed");
	init_struct(&minishell, envp);
	while (1)
	{
		minishell.prompt = calc_prompt(minishell);
		parse_line(&minishell, readline(minishell.prompt));
		update_infos(&minishell);
	}
	free_split(&null_argv);
	return (0);
}

/*
** Function to display an error message and exit the program
*/
void	error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(1);
}

/*
** Free args and exit the program
*/
void	free_exit(t_minishell *minishell, char **args, char *message)
{
	free_struct(minishell);
	free_split(&args);
	rl_clear_history();
	if (message)
		error(message);
	exit(EXIT_SUCCESS);
}
