/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:51:17 by ygille            #+#    #+#             */
/*   Updated: 2025/02/17 15:32:01 by ygille           ###   ########.fr       */
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
	int		mode;
	int		input_file;
	char	*home;
	char	*user;
	char	*pwd;
	char	**envp;
	char	*prompt;
	int		child_pid;
	t_mlist	*env;
	t_list	*garbage;
	t_list	*garbage_split;
}	t_minishell;

typedef struct s_mlist
{
	char	mask;
	t_bool	glue;
	char	*name;
	char	*content;
	t_mlist	*next;
}	t_mlist;

typedef struct s_pipes
{
	int				fd_in;
	int				fd_out;
	t_bool			issue;
	char			*content;
	struct s_pipes	*next;
}	t_pipes;

typedef struct s_pipe_mem
{
	t_pipes	*current;
	int		i;
	int		size;
	int		*pipefd;
	t_bool	is_piped;
}	t_pipe_mem;

enum	e_op_codes
{
	PSET,
	PGET,
	PRESET
};

enum	e_modes
{
	TTY_MODE,
	SCRIPT_MODE,
	NO_TTY_MODE
};

#endif