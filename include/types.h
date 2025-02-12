/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:02:55 by ygille            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/12 10:43:32 by sithomas         ###   ########.fr       */
=======
/*   Updated: 2025/02/12 12:15:50 by ygille           ###   ########.fr       */
>>>>>>> fc85330042b5180c61369bb7a742685f5ce1f74c
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

//	types/mlist.c
t_mlist	*ft_mlstclear(t_mlist *lst);
t_mlist	*ft_mlstcreate(char *name, char *content);
t_mlist	*ft_mlstadd_front(t_mlist *lst, t_mlist *new);
void	ft_mlstdelone(t_mlist *lst);
int		ft_mlstsize(t_mlist *lst);

//	types/mlist2.c
t_mlist	*ft_mlstadd_back(t_mlist *lst, t_mlist *new);
t_mlist	*ft_mlstlast(t_mlist *lst);
t_mlist	*ft_mlstsearch(t_mlist *lst, char *find);

//	types/minishell.c
void	init_struct(t_minishell *minishell, char **envp);
void	free_struct(t_minishell *minishell);
void	update_infos(t_minishell *minishell);

//	types/pipes.c 
t_pipes	*pipeclear(t_pipes *lst);
t_pipes	*pipecreate(char *content);
void	pipeadd_back(t_pipes **lst, t_pipes *new);
void	pipedelone(t_pipes *lst);
int		pipelstsize(t_pipes *lst);

//	types/pipes2.c
t_pipes	*pipelast(t_pipes *lst);

#endif