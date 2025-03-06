/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:44:12 by ygille            #+#    #+#             */
/*   Updated: 2025/03/06 17:11:31 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

//	pipes/multiple_pipes.c
void	multiple_pipes(t_minishell *minishell, t_pipes **unpiped, int size);
void	son(int i, t_pipes *current, int size, int *pipefd);

//	pipes/parse.c 
int		parse_pipe(t_pipes	*new, t_minishell *minishell);

//	pipes/pipes.c
void	unpipe(t_minishell *minishell, char *line);

//	pipes/treat.c
void	fill_here_doc(t_pipes *new, char *tmp, t_minishell *minishell);

//	pipes/treat_env.c
char 	*treat_env(char *str, t_minishell *minishell);

//	pipes/signal_heredoc.c
void	run_heredoc(char *tmp, int pipefd1, int quoted, t_minishell *minishell);

#endif