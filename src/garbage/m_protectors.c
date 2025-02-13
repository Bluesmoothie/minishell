/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_protectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:03:30 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 16:18:53 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Act like malloc but return only on sucess
** register the pointer in a garbage list
** /!\ you need to free this pointer with garbage_release /!\
** if malloc fail, automatically free all garbage and quit
*/
void	*garbage_malloc(t_minishell *minishell, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	garbage_add(minishell, ptr);
	return (ptr);
}

/*
** /!\ you need to free this pointer with garbage_release /!\
*/
char	*garbage_getcwd(t_minishell *minishell)
{
	char	*result;

	result = getcwd(NULL, 0);
	garbage_add(minishell, (void *)result);
	return (result);
}
/*
** /!\ you need to free this pointer with garbage_release /!\
*/
char	*garbage_itoa(t_minishell *minishell, int n)
{
	char	*result;

	result = ft_itoa(n);
	garbage_add(minishell, (void *)result);
	return (result);
}
