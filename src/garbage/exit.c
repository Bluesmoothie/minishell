/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:24:06 by ygille            #+#    #+#             */
/*   Updated: 2025/02/18 14:09:28 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

static void	gexit(void *param, char *message,
				void (*exit_func)(void *param, char *message),
				t_gbool call);

/*
** Indicate to garbage collector wich function to call on error and a
** param to send to it
*/
void	gset_exit(void *param, void (*exit_func)(void *param, char *message))
{
	gexit(param, NULL, exit_func, 0);
}

/*
** Call gclean then
** Call the previously selected exit function
** passing message to it
*/
void	gcall_exit(char *message)
{
	gclean();
	gexit(NULL, message, NULL, 1);
}

/*
** Intern gestion of exit function
*/
static void	gexit(void *param, char *message,
	void (*exit_func)(void *param, char *message), t_gbool call)
{
	static t_exit_func	exit_func_mem = NULL;
	static void			*param_mem = NULL;

	if (call == 0)
	{
		exit_func_mem = exit_func;
		param_mem = param;
	}
	else if (call == 1 && exit_func_mem != NULL)
		exit_func_mem(param_mem, message);
}
