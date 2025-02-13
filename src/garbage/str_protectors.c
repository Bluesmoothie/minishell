/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_protectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:52:14 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 16:19:08 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** del unit is used to del s2 and del / 10 to del s1
** values other from 00 01 10 11 can cause imprevisible error
** /!\ you need to free this pointer with garbage_release /!\
*/
char	*garbage_strfcat(t_minishell *minishell, char *s1, char *s2, int del)
{
	t_bool	del_s1;
	t_bool	del_s2;
	char	*result;

	del_s1 = del / 10;
	del_s2 = del % 10;
	result = ft_strfcat(s1, s2, del_s1, del_s2);
	garbage_add(minishell, (void *)result);
	return (result);
}
/*
** /!\ you need to free this pointer with garbage_release /!\
*/
char	*garbage_substr(t_minishell *minishell, const char *s, unsigned int start, size_t len)
{
	char	*result;

	result = ft_substr(s, start, len);
	garbage_add(minishell, (void *)result);
	return (result);
}
/*
** /!\ you need to free this pointer with garbage_release /!\
*/
char	*garbage_strdup(t_minishell *minishell, const char *s)
{
	char	*result;

	result = ft_strdup(s);
	garbage_add(minishell, (void *)result);
	return (result);
}
/*
** /!\ you need to free this pointer with garbage_release /!\
*/
char	*garbage_strjoin(t_minishell *minishell, const char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	garbage_add(minishell, (void *)result);
	return (result);
}
/*
** /!\ you need to free this pointer with garbage_release /!\
*/
char	*garbage_strtrim(t_minishell *minishell, const char *s1, const char *set)
{
	char	*result;

	result = ft_strtrim(s1, set);
	garbage_add(minishell, (void *)result);
	return (result);
}
