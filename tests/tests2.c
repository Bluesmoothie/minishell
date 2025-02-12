/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:38:57 by ygille            #+#    #+#             */
/*   Updated: 2025/02/12 18:01:16 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	launch_one(char *test, char **envp)
{
	launch_loop(test, envp);
	launch_diff(envp);
}

void	launch_diff(char **envp)
{
	int		pid;
	char	**args;

	args = (char *[]){"/bin/diff", "out.txt", "ref.txt", NULL};
	pid = fork();
	if (pid == 0)
		execve("/bin/diff", args, envp);
	waitpid(pid, NULL, 0);
}

void	launch_loop(char *test, char **envp)
{
	int		fd[2];
	int		result[2];

	unlink("out.txt");
	unlink("ref.txt");
	ft_printf("Test %s : \n", test);
	fd[0] = open(test, O_RDONLY);
	fd[1] = open("out.txt", O_CREAT | O_RDWR, 00777);
	result[0] = launch_test(fd, test, envp);
	close (fd[0]);
	close (fd[1]);
	fd[0] = open(test, O_RDONLY);
	fd[1] = open("ref.txt", O_CREAT | O_RDWR, 00777);
	result[1] = launch_ref(fd, test, envp);
	close (fd[0]);
	close (fd[1]);
	if (result[0] != result[1])
		ft_printf("Diff in return values\nbash = %d mini = %d\n",
			result[1], result[0]);
}
