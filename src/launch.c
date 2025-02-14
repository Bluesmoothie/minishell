/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:49:35 by ygille            #+#    #+#             */
/*   Updated: 2025/02/14 23:48:29 by ygille           ###   ########.fr       */
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
		gfree_double(new_envp);
		gcall_exit(E_FORK);
	}
	if (pid == 0)
		execve(path, args, new_envp);
	waitpid(pid, &minishell->last_return_value, 0);
	gfree_double(new_envp);
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
		new_envp[--size] = ft_strfcat(ft_strfcat(list->name, "=", FALSE, FALSE),
				list->content, TRUE, FALSE);
		if (new_envp[size] == NULL)
		{
			gfree_double(new_envp);
			return (NULL);
		}
		list = list->next;
	}
	return (new_envp);
}
