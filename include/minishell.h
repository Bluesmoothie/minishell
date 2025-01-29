/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:27 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 01:27:41 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "text_formats.h"
# include "error_messages.h"

# include "libft.h"

# define FALSE 0
# define TRUE 1

typedef unsigned char	t_bool;

//	minishell.c
void	error(char *message);
void	free_exit(char **args, char *message);

//	functions.c
void	func_echo(char **args);
void	func_cd(char **args);
void	func_pwd(void);
void	func_export(char **args);
void	func_unset(char **args);

//	functions2.c
void	func_env(void);

//	parse.c
void	parse_line(char *line);
t_bool	builtin_functions(char **args);
void	try_launch(char **args);

//	text.c
void	display_text(char *text, char format[5], char color[6]);
char	*calc_prompt(void);
char	*get_relative_path(void);

//	utils.c
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *s1, char *s2);
char	*ft_strfcat(char *s1, char *s2, t_bool fs1, t_bool fs2);
void	free_split(char **split);

#endif