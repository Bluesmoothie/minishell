/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:51:17 by ygille            #+#    #+#             */
/*   Updated: 2025/02/11 17:06:50 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_minishell	t_minishell;
typedef struct s_mlist		t_mlist;
typedef struct s_pipes		t_pipes;

typedef struct s_minishell
{
	int		last_return_value;
	char	*home;
	char	*user;
	char	*pwd;
	char	**envp;
	char	*prompt;
	t_mlist	*env;
}	t_minishell;

typedef struct s_mlist
{
	char	mask;
	char	*name;
	char	*content;
	t_mlist	*next;
}	t_mlist;

typedef struct s_pipes
{
	int				fd_in;
	int				fd_out;
	char			*content;
	struct s_pipes	*next;
}				t_pipes;

#endif