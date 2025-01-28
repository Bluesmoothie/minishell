/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:13 by ygille            #+#    #+#             */
/*   Updated: 2024/11/27 14:01:09 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	100000
# endif

# include <unistd.h>
# include <stdlib.h>
# include <libft.h>

//get_next_line.c
char	*get_next_line(int fd);
char	*read_buff(int fd, char **mem, char *buff, int *state);
char	*extract_line(char **mem, int *state);
char	*update_mem(char *mem);
int		check_mem(char **mem, int *state);

#endif