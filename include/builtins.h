/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:03:25 by ygille            #+#    #+#             */
/*   Updated: 2025/02/15 12:45:45 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//	builtins/cd.c
int		func_cd(t_minishell *minishell, char **args);

//	builtins/echo.c
int		func_echo(char **args, int fd);

//	builtins/env.c
int		func_env(t_minishell *minishell, int fd);

//	builtins/export.c
int		func_export(t_minishell *minishell, char **args, int fd);
void	replace_env(t_minishell *minishell, char *name, char *content);
char	*extract_name(char *arg);
char	*extract_content(char *arg);

//	builtins/pwd.c
int		func_pwd(t_minishell *minishell, int fd);

//	builtins/unset.c
int		func_unset(t_minishell *minishell, char **args);

#endif