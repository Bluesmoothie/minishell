/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:49:35 by ygille            #+#    #+#             */
/*   Updated: 2025/01/30 17:15:32 by ygille           ###   ########.fr       */
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
	if (new_envp == NULL)
		free_exit(minishell, args, E_MALLOCFAIL);
	pid = fork();
	if (pid == -1)
	{
		free_split(&new_envp);
		free_exit(minishell, args, "fork failed");
	}
	if (pid == 0)
		exit (execve(path, args, new_envp));
	if (waitpid(pid, &minishell->last_return_value, 0) == -1)
		error("waitpid failed");
	free_split(&new_envp);
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
		path = ft_strfcat(ft_strfcat(paths[i], "/", FALSE, FALSE),
				bin, TRUE, FALSE);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
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
	new_envp = malloc(sizeof(char *) * (size + 1));
	if (new_envp == NULL)
		return (NULL);
	new_envp[size] = NULL;
	list = minishell->env;
	while (list != NULL)
	{
		new_envp[--size] = ft_strfcat(ft_strfcat(list->name, "=", FALSE, FALSE),
				list->content, TRUE, FALSE);
		if (new_envp[size] == NULL)
		{
			free_split(&new_envp);
			return (NULL);
		}
		list = list->next;
	}
	return (new_envp);
}
