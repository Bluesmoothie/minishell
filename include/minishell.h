/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:27 by ygille            #+#    #+#             */
/*   Updated: 2025/01/29 19:49:56 by ygille           ###   ########.fr       */
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

typedef unsigned char		t_bool;
typedef struct s_minishell	t_minishell;
typedef struct s_mlist		t_mlist;

typedef struct s_minishell
{
	int		last_return_value;
	char	*home;
	char	*user;
	char	*pwd;
	char	**envp;
	char	*prompt;
	t_mlist	*env;
}	t_minishell;

typedef struct s_mlist
{
	char	*name;
	char	*content;
	t_mlist	*next;
}	t_mlist;

//	minishell.c
void	error(char *message);
void	free_exit(t_minishell *minishell, char **args, char *message);

//	mlist.c
t_mlist	*ft_mlstclear(t_mlist *lst);
t_mlist	*ft_mlstcreate(char *name, char *content);
t_mlist	*ft_mlstadd_front(t_mlist *lst, t_mlist *new);
void	ft_mlstdelone(t_mlist *lst);

//	parse.c
void	parse_line(t_minishell *minishell, char *line);
t_bool	builtin_functions(t_minishell *minishell, char **args);
void	try_launch(char **args);
void	search_for_env(t_minishell *minishell, char ***args);
char	*get_env_value(t_minishell *minishell, char *name);

//	struct.c
void	init_struct(t_minishell *minishell, char **envp);
void	free_struct(t_minishell *minishell);
void	update_infos(t_minishell *minishell);
t_mlist	*init_env(char **envp);

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
int		func_cd(t_minishell *minishell, char **args);

//	builtins/echo.c
int		func_echo(t_minishell *minishell, char **args);

//	builtins/env.c
int		func_env(t_minishell *minishell);

//	builtins/export.c
int		func_export(t_minishell *minishell, char **args);
char	*extract_name(char *arg);
char	*extract_content(char *arg);

//	builtins/pwd.c
int		func_pwd(t_minishell *minishell);

//	builtins/unset.c
int		func_unset(t_minishell *minishell, char **args);

#endif