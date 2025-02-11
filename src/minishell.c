/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:41 by ygille            #+#    #+#             */
/*   Updated: 2025/02/11 22:18:39 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// int			pid;
	// char		**null_argv;
	char		*line;
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	// null_argv = (char *[]){"", NULL};
	// pid = fork();
	// if (pid == -1)
	// 	error("fork failed");
	// if (pid == 0)
	// 	execve("/bin/clear", null_argv, envp);
	// if (waitpid(pid, NULL, 0) == -1)
	// 	error("waitpid failed");
	init_minishell(&minishell, envp);
	while (1)
	{
		line = get_line(&minishell);
		parse_line(&minishell, line);
		update_infos(&minishell);
	}
	return (0);
}

char	*get_line(t_minishell *minishell)
{
	char	*line;
	char	*tmp;

	if (isatty(STDIN_FILENO))
		return (readline(minishell->prompt));
	line = get_next_line(STDIN_FILENO);
	if (line)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
	}
	return(line);
}

/*
** Function to display an error message and exit the program
*/
void	error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
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
