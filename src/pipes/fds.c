/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:19:51 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/16 16:17:07 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fd_size(t_pipes *first);

int	*establish_fd_list(t_pipes *first)
{
	int		*result;
	t_pipes	*current;
	int		size;

	size = get_fd_size(first);
	if (size == 0)
		return (0);
	current = first;
	result = (int *)gmalloc((size + 1) * sizeof(int));
	size = 0;
	while (current)
	{
		if (!isatty(current->fd_in))
			result[size++] = current->fd_in;
		if (!isatty(current->fd_out))
			result[size++] = current->fd_out;
		current = current->next;
	}
	result[size] = 0;
	return (result);
}

static int	get_fd_size(t_pipes *first)
{
	t_pipes	*current;
	int		size;

	current = first;
	size = 0;
	while (current)
	{
		if (!isatty(current->fd_in))
			size++;
		if (!isatty(current->fd_out))
			size++;
		current = current->next;
	}
	return (size);
}

int	open_null_fd(void)
{
	int	result;

	result = open("/dev/null", O_RDWR);
	if (result == -1)
		printf(E_OPEN);
	return (result);
}

void	delete_after_pos(t_pipes *new, int pos)
{
	while (new->content[pos])
	{
		new->content[pos] = '\0';
		pos++;
	}
}
