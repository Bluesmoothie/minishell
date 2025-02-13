/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:49:35 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 17:05:45 by ygille           ###   ########.fr       */
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
	pid = fork();
	if (pid == -1)
	{
		garbage_release_split(minishell, &new_envp);
		free_exit(minishell, E_FORK);
	}
	if (pid == 0)
		execve(path, args, new_envp);
	waitpid(pid, &minishell->last_return_value, 0);
	garbage_release_split(minishell, &new_envp);
}

/*
** Search the binary in the PATH
** if found, return the path or NULL if not found
*/
char	*search_binary(t_minishell *minishell, char **paths, char *bin)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		path = garbage_strfcat(minishell, garbage_strfcat(minishell, paths[i], "/", 0),
				bin, 10);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		garbage_release(minishell, (void *)path);
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
	new_envp = garbage_malloc(minishell, sizeof(char *) * (size + 1));
	new_envp[size] = NULL;
	list = minishell->env;
	while (list != NULL)
	{
		new_envp[--size] = garbage_strfcat(minishell, garbage_strfcat(minishell, list->name, "=", 0),
				list->content, 10);
		if (new_envp[size] == NULL)
		{
			garbage_release_split(minishell, &new_envp);
			return (NULL);
		}
		list = list->next;
	}
	return (new_envp);
}
