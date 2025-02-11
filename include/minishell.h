/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:27 by ygille            #+#    #+#             */
/*   Updated: 2025/02/11 14:10:50 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

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
	char	mask;
	char	*name;
	char	*content;
	t_mlist	*next;
}	t_mlist;

typedef struct	s_pipes
{
	int				fd_in;
	int				fd_out;
	char			*content;
	struct s_pipes	*next;
}				t_pipes;

//	minishell.c
void	error(char *message);
void	free_exit(t_minishell *minishell, char **args, char *message);

// env.c
void	search_for_env(t_minishell *minishell, t_mlist	*args);
char	*get_env_name(t_minishell *minishell, char *arg);
char	*get_env_value(t_minishell *minishell, char *name);
void	replace_env_value(t_minishell *minishell, t_mlist *node, char *value);
char	*update_searching(t_minishell *minishell, char *name, int i);

//	init.c
void	init_minishell(t_minishell *minishell, char **envp);
void	init_signals(void);
void	init_term(void);
t_mlist	*init_env(char **envp);

//	launch.c
void	launch_bin(t_minishell *minishell, char *path, char **args);
char	*search_binary(char **paths, char *bin);
char	**create_new_envp(t_minishell *minishell);

//	miniparse.c
char	**miniparse(t_minishell *minishell, char *line);
int		skip_whitespaces(char *line);
int		extract_arg(t_minishell *minishell, char *line, t_mlist **args);
char	**rebuild_args(t_minishell *minishell, t_mlist *args);
t_mlist	*extract_helper(t_minishell *minishell, char *line, int i, char sep);

//	mlist.c
t_mlist	*ft_mlstclear(t_mlist *lst);
t_mlist	*ft_mlstcreate(char *name, char *content);
t_mlist	*ft_mlstadd_front(t_mlist *lst, t_mlist *new);
void	ft_mlstdelone(t_mlist *lst);
int		ft_mlstsize(t_mlist *lst);

//	mlist2.c
t_mlist	*ft_mlstadd_back(t_mlist *lst, t_mlist *new);
t_mlist	*ft_mlstlast(t_mlist *lst);
t_mlist	*ft_mlstsearch(t_mlist *lst, char *find);

//	parse.c
void	parse_line(t_minishell *minishell, char *line);
void	treat_arguments(t_minishell *minishell, char *line, int fd);
t_bool	builtin_functions(t_minishell *minishell, char **args, int fd);
void	try_launch(t_minishell *minishell, char **args);
char	*calc_bin_path(t_minishell *minishell, char **args);

//	pipes.c
void	unpipe(t_minishell *minishell, char *line);

//	signals.c
void	signal_handler(int sig);

//	struct.c
void	init_struct(t_minishell *minishell, char **envp);
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
int		func_cd(t_minishell *minishell, char **args);

//	builtins/echo.c
int		func_echo(t_minishell *minishell, char **args, int fd);

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

//t_pipes.c 
t_pipes	*pipeclear(t_pipes *lst);
t_pipes	*pipecreate(char *content);
void	pipeadd_back(t_pipes **lst, t_pipes *new);
void	pipedelone(t_pipes *lst);
int	pipelstsize(t_mlist *lst);
t_pipes	*pipelast(t_pipes *lst);

#endif