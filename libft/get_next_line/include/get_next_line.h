/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:13 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 19:56:43 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	100000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX	100
# endif

# define MAX_INT		2147483647

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"

char	*get_next_line(int fd);
char	*read_buff(int fd, char **mem, char *buff, int *state);
char	*extract_line(char **mem);
char	*update_mem(char *mem);
int		check_mem(char **mem);

#endif