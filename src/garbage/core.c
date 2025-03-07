/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:01:28 by ygille            #+#    #+#             */
/*   Updated: 2025/03/06 17:49:22 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

static void	garbage_add(void *glist[], size_t *gsize, void *ptr);
static void	garbage_remove(void *glist[], size_t *gsize, void *ptr);
static void	garbage_clean(void *glist[], size_t *gsize);
static void	garbage_error(char *message);

/*
** Internal use of garbage collector only
** apply requested operation
*/
void	garbage_col(int op_code, void *ptr)
{
	static void		*glist[GARBAGE_SIZE];
	static size_t	act_gsize = 0;

	if (op_code == GADDPTR)
		garbage_add(glist, &act_gsize, ptr);
	else if (op_code == GRMPTR)
		garbage_remove(glist, &act_gsize, ptr);
	else if (op_code == GCLEANALL)
		garbage_clean(glist, &act_gsize);
}

/*
** Add a ptr to the list
*/
static void	garbage_add(void *glist[], size_t *gsize, void *ptr)
{
	if (ptr == NULL)
		return ;
	if (*gsize == GARBAGE_SIZE)
		return (garbage_error(EGFULL));
	glist[*gsize] = ptr;
	(*gsize)++;
}

/*
** Remove a ptr from the list
*/
static void	garbage_remove(void *glist[], size_t *gsize, void *ptr)
{
	size_t	i;

	if (*gsize == 0 || ptr == NULL)
		return ;
	i = 0;
	while (i < *gsize && glist[i] != ptr)
		i++;
	if (i == *gsize)
		return ;
	glist[i] = NULL;
	free (ptr);
	if (i < *gsize - 1)
	{
		glist[i] = glist[*gsize - 1];
		glist[*gsize - 1] = NULL;
	}
	(*gsize)--;
}

/*
** Free all memory allocated with garbage collector
*/
static void	garbage_clean(void *glist[], size_t *gsize)
{
	size_t	i;

	i = 0;
	while (i < *gsize)
	{
		if (glist[i] != NULL)
			free (glist[i]);
		glist[i] = NULL;
		i++;
	}
	*gsize = 0;
}

/*
** Print the message on the standar error output
*/
static void	garbage_error(char *message)
{
	size_t	i;

	i = 0;
	while (message[i] != '\0')
		i++;
	if (i > 0)
		write(STDERR_FILENO, message, i);
}
