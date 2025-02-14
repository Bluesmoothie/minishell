/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:47:53 by ygille            #+#    #+#             */
/*   Updated: 2025/02/14 23:51:50 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include "libft.h"

# define TRUE					1
# define FALSE					0

# ifndef GARBAGE_SIZE
#  define GARBAGE_SIZE			2048
# endif
# ifndef GARBAGE_SPLIT_SIZE
#  define GARBAGE_SPLIT_SIZE	1024
# endif
# ifndef GARBAGE_WARN_NF
#  define GARBAGE_WARN_NF		FALSE
# endif

# define EGNF			"Warning : can't found requested ptr in ptr list"
# define EGFULL			"Error : garbage full, try increase GARBAGE_SIZE"
# define EGMALLOC		"Garbage collector has detected a malloc error"

enum	e_gop_codes
{
	GADDPTR,
	GRMPTR,
	GCLEANALL
};

typedef void			(*t_exit_func)(void *, char *);
typedef	unsigned char	t_gbool;

//	garbage/core.c
void	garbage_col(int op_code, void *ptr);

//	garbage/double_core.c
void	double_garbage_col(int op_code, void **ptr);

//	garbage//double.c
void	*gmalloc_double(size_t size);
void	gfree_double(void *ptr);
void	gfree_double_helper(void **ptr);

//	garbage//exit.c
void	gset_exit(void *param, void (*exit_func)(void *param, char *message));
void	gcall_exit(char *message);

//	garbage/interface.c
void	*gmalloc(size_t size);
void	gfree(void *ptr);
void	gclean(void);

#endif