/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:47:53 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 16:23:32 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GARBAGE_H
# define GARBAGE_H

//	garbage/garbage.c
void	garbage_add(t_minishell *minishell, void *ptr);
void	garbage_destroy(t_minishell *minishell);
void	garbage_release(t_minishell *minishell, void *ptr);

//	garbage/m_protectors.c
void	*garbage_malloc(t_minishell *minishell, size_t size);
char	*garbage_getcwd(t_minishell *minishell);
char	*garbage_itoa(t_minishell *minishell, int n);

//	garbage/s_protectors.c
void	protec_pipe(t_minishell *minishell, int *__pipesdes);

//	garbage/s_protectors2.c
void	protec_open(t_minishell *minishell, const char *__file, int __oflag);
void	protec_close(t_minishell *minishell, int fd);
int		protec_waitpid(t_minishell *minishell, pid_t pid);
int		protec_dup(t_minishell *minishell, int __fd);
void	protec_dup2(t_minishell *minishell, int __fd, int __fd2);

//	garbage/split_garbage.c
char	**garbage_split(t_minishell *minishell, const char *s, char c);
void	garbage_add_split(t_minishell *minishell, void *ptr);
void	garbage_release_split(t_minishell *minishell, void *ptr);
void	garbage_destroy_split(t_list *list);
void	garbage_free_split(void *list);

//	garbage/str_protectors.c
char	*garbage_strfcat(t_minishell *minishell, char *s1, char *s2, int del);
char	*garbage_substr(t_minishell *minishell, const char *s, unsigned int start, size_t len);
char	*garbage_strdup(t_minishell *minishell, const char *s);
char	*garbage_strjoin(t_minishell *minishell, const char *s1, const char *s2);
char	*garbage_strtrim(t_minishell *minishell, const char *s1, const char *set);

#endif