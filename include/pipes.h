/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:44:12 by ygille            #+#    #+#             */
/*   Updated: 2025/02/12 17:22:35 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

//	pipes/multiple_pipes.c
void	multiple_pipes(t_minishell *minishell, t_pipes **unpiped, int size);

//	pipes/parse.c 
void	parse_pipe(t_pipes	*new);

//	pipes/pipes.c
void	unpipe(t_minishell *minishell, char *line);
void	unpipe2(t_minishell *minishell, char *line);

//	pipes/treat.c
void	treat_pipe(t_minishell *minishell, t_pipes *unpiped);
int		fill_here_doc(t_pipes *new, char *tmp);

#endif