/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:47:53 by ygille            #+#    #+#             */
/*   Updated: 2025/02/14 18:12:53 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include "libft.h"

# ifndef GARBAGE_SIZE
#  define GARBAGE_SIZE			2048
# endif
# ifndef GARBAGE_SPLIT_SIZE
#  define GARBAGE_SPLIT_SIZE	1024
# endif
# ifndef GARBAGE_WARN_NF
#  define GARBAGE_WARN_NF		FALSE
# endif

# define E_GNF			"Warning : can't found requested ptr in ptr list"
# define E_GFULL		"Error : garbage full, try increase GARBAGE_SIZE"

enum	e_gop_codes
{
	ADDPTR,
	RMPTR
};

void	garbage_col(int op_code, void *ptr);
void	garbage_add(void *glist[], size_t *gsize, void *ptr);
void	garbage_remove(void *glist[], size_t *gsize, void *ptr);
void	garbage_error(char *message);

#endif