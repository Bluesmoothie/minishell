/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:27 by ygille            #+#    #+#             */
/*   Updated: 2025/02/14 18:08:32 by ygille           ###   ########.fr       */
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

# include "libft.h"
# include "get_next_line.h"

# include "struct.h"
# include "builtins.h"
# include "error_messages.h"
# include "garbage.h"
# include "pipes.h"
# include "text_formats.h"
# include "types.h"

//	minishell.c
void	define_mode(t_minishell *minishell, int argc, char **argv);
char	*get_line(t_minishell *minishell);
void	error(char *message);
void	free_exit(t_minishell *minishell, char *message);

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
void	signal_handler(int sig);

//	launch.c
void	launch_bin(t_minishell *minishell, char *path, char **args);
char	*search_binary(char **paths, char *bin);
char	**create_new_envp(t_minishell *minishell);

//	miniparse.c
char	**miniparse(t_minishell *minishell, char *line);
int		skip_whitespaces(char *line);
int		extract_arg(t_minishell *minishell, char *line,
			t_mlist **args, t_mlist **node);
char	**rebuild_args(t_minishell *minishell, t_mlist *args);
t_mlist	*extract_helper(t_minishell *minishell, char *line, int i, char sep);

//	parse.c
void	parse_line(t_minishell *minishell, char *line);
void	treat_arguments(t_minishell *minishell, char *line, int fd);
t_bool	builtin_functions(t_minishell *minishell, char **args, int fd);
void	try_launch(t_minishell *minishell, char **args);
char	*calc_bin_path(t_minishell *minishell, char **args);

//	text.c
void	display_text(char *text, char format[5], char color[6]);
void	display_error(char *command, char *error, char *arg);
char	*calc_prompt(t_minishell minishell);
char	*get_relative_path(char *pwd, char *home);

//	utils.c
char	**extract_str(char *str, int beg, int end);

#endif