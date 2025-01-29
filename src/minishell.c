/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:41 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 01:24:20 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	char	*prompt;

	(void)argc;
	pid = fork();
	if (pid == -1)
		error("fork failed");
	if (pid == 0)
		execve("/bin/clear", argv, envp);
	if (waitpid(pid, NULL, 0) == -1)
		error("waitpid failed");
	while (1)
	{
		prompt = calc_prompt();
		parse_line(readline(prompt));
		free(prompt);
	}
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
void	free_exit(char **args, char *message)
{
	free_split(args);
	rl_clear_history();
	if (message)
		error(message);
	exit(EXIT_SUCCESS);
}
