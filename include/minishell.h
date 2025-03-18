/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:27 by ygille            #+#    #+#             */
/*   Updated: 2025/03/18 16:03:49 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"

# ifndef PROMPT_COLOR
#  define PROMPT_COLOR FALSE
# endif

# include "struct.h"
# include "builtins.h"
# include "error_messages.h"
# include "garbage.h"
# include "pipes.h"
# include "text_formats.h"
# include "types.h"

//	minishell.c
void		define_mode(t_minishell *minishell, int argc, char **argv);
char		*get_line(t_minishell *minishell);
void		error(char *message);
void		free_exit(void *param, char *message);

//	builtins.c
t_bool		is_builtin(char **args);
void		piped_builtin(t_minishell *minishell, char **args);

//	env.c
void		search_for_env(t_minishell *minishell, t_mlist	*args);
char		*get_env_name(char *arg);
char		*get_env_value(t_minishell *minishell, char *name);
void		replace_env_value(t_mlist *node, char *value);
char		*update_searching(char *name, int i);

//	env2.c
void		update_pwdvar(t_minishell *minishell);
void		update_content(t_mlist *arg);

//	init.c
void		init_minishell(t_minishell *minishell, char **envp);
void		init_signals(void);
void		init_term(void);
t_mlist		*init_env(char **envp);
void		term_param_restore(t_termios param, t_bool restore);

//	launch.c
void		launch_bin(t_minishell *minishell, char *path, char **args);
void		launch_bin_piped(t_minishell *minishell, char *path, char **args,
				char **envp);
char		*search_binary(char **paths, char *bin);
char		**create_new_envp(t_minishell *minishell);

//	miniparse.c
char		**miniparse(t_minishell *minishell, char *line);
int			skip_whitespaces(char *line);
int			extract_arg(char *line, t_mlist **args, t_mlist **node);
char		**rebuild_args(t_mlist *args);
t_mlist		*extract_helper(char *line, int i, char sep);

//	nf.c
int			fork_nf(t_minishell *minishell, char *comm);
int			display_nf(char *arg);

//	parse.c
void		parse_line(t_minishell *minishell, char *line);
void		treat_arguments(t_minishell *minishell, char *line, int fd);
t_bool		builtin_functions(t_minishell *minishell, char **args, int fd);
void		try_launch(t_minishell *minishell, char **args);
char		*calc_bin_path(t_minishell *minishell, char **args);

//	pid_connect.c
void		add_pid(int pid, int index, int size);
void		reset_pid(void);
int			*get_pid(void);

//	pipe_connect.c
t_bool		is_piped(void);
void		set_pipe(int i, t_pipes *current, int size, int *pipefd);
void		reset_pipe(void);
t_pipe_mem	get_pipe(void);

//	quotes.c
int			*quotes_verif(char *line);

//	quotes_chevron.c
t_bool		*quotes_verif_chevron(char *line);

//	signal.c
void		siginit_struct(t_minishell *minishell);
void		signal_handler(int sig);

//	text.c
void		display_text(char *text, char format[5], char color[6], int fd);
void		display_error(char *command, char *error, char *arg);
char		*calc_prompt(t_minishell minishell);
char		*get_relative_path(char *pwd, char *home);

//	utils.c
char		**extract_str(char *str, int beg, int end);
char		*verif_file(char *path);
void		returns_process(int code, t_return *ret);
char		*trimndelete(char *str, char *set);

#endif