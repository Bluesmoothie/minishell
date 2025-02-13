/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:36:28 by ygille            #+#    #+#             */
/*   Updated: 2025/02/12 17:58:47 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(int argc, char **argv, char **envp)
{
	char	*test;

	if (argc < 2)
		launch_all(envp);
	else if (argc > 2)
		exit (ft_printf("Choose a test or nothing for all\n"));
	else
	{
		test = ft_strjoin(ft_strjoin("tests/", argv[1]), ".sh");
		if (test == NULL)
			exit (1);
		launch_one(test, envp);
		launch_diff(envp);
	}
}

int	launch_all(char **envp)
{
	char	**test_list;

	test_list = init_list();
	while (*test_list != NULL)
	{
		launch_loop(*test_list, envp);
		launch_diff(envp);
		test_list++;
	}
	return (0);
}

char	**init_list(void)
{
	static char	*tests[] = {
		"tests/chevron.sh",
		"tests/echo.sh",
		"tests/env.sh",
		"tests/others.sh",
		"tests/pipes.sh",
		"tests/quotes",
		"tests/return.sh",
		NULL};

	return (tests);
}

int	launch_test(int fd[2], char *test, char **envp)
{
	int		pid;
	int		return_val;
	char	**args;

	args = (char *[]){"./minishell", test, NULL};
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve("./minishell", args, envp);
	}
	waitpid(pid, &return_val, 0);
	return (return_val);
}

int	launch_ref(int fd[2], char *test, char **envp)
{
	int		pid;
	int		return_val;
	char	**args;

	args = (char *[]){"/bin/bash", test, NULL};
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve("/bin/bash", args, envp);
	}
	waitpid(pid, &return_val, 0);
	return (return_val);
}
