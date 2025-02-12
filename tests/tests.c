/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:36:28 by ygille            #+#    #+#             */
/*   Updated: 2025/02/12 17:21:45 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(int argc, char **argv, char **envp)
{
	char	**test_list;
	int		result[2];
	int		fd[2];

	(void)argc;
	(void)argv;
	test_list = init_list();
	while (*test_list != NULL)
	{
		ft_printf("Test %s : \n", *test_list);
		fd[0] = open(*test_list, O_RDONLY);
		fd[1] = open("out.txt", O_CREAT | O_RDWR, 00777);
		result[0] = launch_test(fd, *test_list, envp);
		close (fd[0]);
		close (fd[1]);
		fd[0] = open(*test_list, O_RDONLY);
		fd[1] = open("ref.txt", O_CREAT | O_RDWR, 00777);
		result[1] = launch_ref(fd, *test_list, envp);
		close (fd[0]);
		close (fd[1]);
		if (result != bash)
			ft_printf("Diff in return values\nbash = %d mini = %d\n",
				result[1], result[0]);
		test_list++;
	}
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

	args = (char *[]){test, NULL};
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

	args = (char *[]){test, NULL};
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
