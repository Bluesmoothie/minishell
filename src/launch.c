/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:49:35 by ygille            #+#    #+#             */
/*   Updated: 2025/02/18 15:31:28 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Launch the binary with the arguments
** and wait for the end of the process
*/
void	launch_bin(t_minishell *minishell, char *path, char **args)
{
	char	**new_envp;
	int		pid;

	new_envp = create_new_envp(minishell);
	if (!is_piped())
	{
		pid = fork();
		if (pid == -1)
			gcall_exit(E_FORK);
		if (pid == 0)
			if (execve(path, args, new_envp) == -1)
				exit (EXIT_FAILURE);
		minishell->child_pid = pid;
		waitpid(pid, &minishell->last_return_value, 0);
		minishell->child_pid = 0;
	}
	else
		launch_bin_piped(minishell, path, args, new_envp);
	gfree_double(new_envp);
}

/*
** Alternate process to handle piped launch
*/
void	launch_bin_piped(t_minishell *minishell, char *path, char **args,
	char **envp)
{
	int			pid;
	t_pipe_mem	pipe;

	pipe = get_pipe();
	pid = fork();
	if (pid == -1)
		gcall_exit(E_FORK);
	if (pid == 0)
	{
		son(pipe.i, pipe.current, pipe.size, pipe.pipefd);
		if (execve(path, args, envp) == -1)
			exit (EXIT_FAILURE);
	}
	add_pid(pid, pipe.i, pipe.size);
	minishell->child_pid = pid;
}

/*
** Search the binary in the PATH
** if found, return the path or NULL if not found
*/
char	*search_binary(char **paths, char *bin)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		path = gman_add(ft_strfcat(ft_strfcat(paths[i], "/", FALSE, FALSE),
					bin, TRUE, FALSE));
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		gfree(path);
		i++;
	}
	return (NULL);
}

/*
** Create a new envp from the list of environment variables
*/
char	**create_new_envp(t_minishell *minishell)
{
	char	**new_envp;
	t_mlist	*list;
	int		size;

	size = ft_mlstsize(minishell->env);
	new_envp = gmalloc_double(sizeof(char *) * (size + 1));
	new_envp[size] = NULL;
	list = minishell->env;
	while (list != NULL)
	{
		new_envp[--size] = gman_add(ft_strfcat(ft_strfcat(list->name, "=",
						FALSE, FALSE), list->content, TRUE, FALSE));
		list = list->next;
	}
	return (new_envp);
}

void	fork_nf(t_minishell *minishell, char *comm)
{
	int			pid;
	t_pipe_mem	pipe;

	pipe = get_pipe();
	pid = 0;
	display_error(comm, E_COMMANDNF, NULL);
	add_pid(pid, pipe.i, pipe.size);
	minishell->child_pid = pid;
}
