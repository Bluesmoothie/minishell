/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:27 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 17:23:22 by ygille           ###   ########.fr       */
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

# define FALSE		0
# define TRUE		1

typedef unsigned char	t_bool;

typedef	struct	s_minishell
{
	int		last_return_value;
	char	*home;
	char	*user;
	char	*pwd;
	char	**path;
	char	**envp;
	char	*prompt;
}	t_minishell;


//	minishell.c
void	error(char *message);
void	free_exit(t_minishell *minishell, char **args, char *message);

//	parse.c
void	parse_line(t_minishell *minishell, char *line);
t_bool	builtin_functions(t_minishell *minishell, char **args);
void	try_launch(char **args);

//	struct.c
void	init_struct(t_minishell *minishell);
void	free_struct(t_minishell *minishell);
void	update_infos(t_minishell *minishell);

//	text.c
void	display_text(char *text, char format[5], char color[6]);
void	display_error(char *command, char *error, char *arg);
char	*calc_prompt(t_minishell minishell);
char	*get_relative_path(char *pwd, char *home);

//	utils.c
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *s1, char *s2);
char	*ft_strfcat(char *s1, char *s2, t_bool fs1, t_bool fs2);
void	free_split(char ***split);

//	builtins/cd.c
void	func_cd(t_minishell *minishell, char **args);

//	builtins/echo.c
void	func_echo(t_minishell *minishell, char **args);
void	echo_arg(t_minishell *minishell, char **args);

//	builtins/env.c
void	func_env(t_minishell *minishell);

//	builtins/export.c
void	func_export(t_minishell *minishell, char **args);

//	builtins/pwd.c
void	func_pwd(t_minishell *minishell);

//	builtins/unset.c
void	func_unset(t_minishell *minishell, char **args);

#endif