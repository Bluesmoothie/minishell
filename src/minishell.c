/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:41 by ygille            #+#    #+#             */
/*   Updated: 2025/01/28 19:58:56 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		pid;

	(void)argc;
	pid = fork();
	if (pid == -1)
		error("fork failed");
	if (pid == 0)
		execve("/bin/clear", argv, envp);
	if (waitpid(pid, NULL, 0) == -1)
		error("waitpid failed");
	while (1)
		parse_line(readline(PROMPT_STYLE));
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
