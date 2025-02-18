/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:44:12 by ygille            #+#    #+#             */
/*   Updated: 2025/02/18 18:50:01 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

//	pipes/multiple_pipes.c
void	multiple_pipes(t_minishell *minishell, t_pipes **unpiped, int size);
void	son(int i, t_pipes *current, int size, int *pipefd);

//	pipes/parse.c 
int		parse_pipe(t_pipes	*new);

//	pipes/pipes.c
void	unpipe(t_minishell *minishell, char *line);

//	pipes/treat.c
int	fill_here_doc(int fd_in, char *tmp);

#endif