/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:44:12 by ygille            #+#    #+#             */
/*   Updated: 2025/03/05 18:47:35 by sithomas         ###   ########.fr       */
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
int		fill_here_doc(t_pipes *new, char *tmp, t_minishell *minishell);

//	pipes/treat_env.c
char *treat_env(char *str, t_minishell *minishell);

#endif