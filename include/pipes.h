/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:44:12 by ygille            #+#    #+#             */
/*   Updated: 2025/03/19 12:28:16 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

//	pipes/multiple_pipes.c
void	multiple_pipes(t_minishell *minishell, t_pipes **unpiped, int size);
void	son(int i, t_pipes *current, int size, int *pipefd);

//	pipes/parse.c 
int		parse_pipe(t_pipes	*new, t_minishell *minishell);
char	*pipe_helper(t_pipes *new, int pos, int param);
int		check_path(char *path);

//	pipes/left_pipe.c
int		left_pipe(t_pipes *new, int pos, t_minishell *minishell, t_bool **quote_checker);

//	pipes/pipes.c
void	unpipe(t_minishell *minishell, char *line, int *pos);

//	pipes/treat.c
int		fill_here_doc(t_pipes *new, char *tmp, t_minishell *minishell);

//	pipes/treat_env.c
char	*treat_env(char *str, t_minishell *minishell);

//	pipes/signal_heredoc.c
void	run_heredoc(char *tmp, int pipefd1, int quoted, t_minishell *minishell);

//	pipes/split_quotes.c
char	**split_quotes(char *line, int *pos);

//	pipes/fds.c
int		*establish_fd_list(t_pipes *first);

#endif