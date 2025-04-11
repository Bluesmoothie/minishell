/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:51:17 by ygille            #+#    #+#             */
/*   Updated: 2025/04/11 10:30:46 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_minishell	t_minishell;
typedef struct s_mlist		t_mlist;
typedef struct s_pipes		t_pipes;
typedef struct termios		t_termios;
typedef struct stat			t_stat;

typedef struct s_return
{
	int		exit_stat;
	int		stopsig;
	int		termsig;
	t_bool	exited;
	t_bool	signaled;
	t_bool	coredump;
	t_bool	stopped;		
}	t_return;

typedef struct s_minishell
{
	int			last_return_value;
	int			mode;
	int			input_file;
	int			child_pid;
	char		*home;
	char		*user;
	char		*pwd;
	char		**envp;
	char		*prompt;
	t_mlist		*env;
	t_return	returns;
}	t_minishell;

typedef struct s_mlist
{
	char	mask;
	char	*name;
	char	*content;
	t_bool	glue;
	t_mlist	*next;
}	t_mlist;

typedef struct s_pipes
{
	int				fd_in;
	int				fd_out;
	t_bool			issue;
	t_bool			skip;
	char			*content;
	struct s_pipes	*next;
}	t_pipes;

typedef struct s_pipe_mem
{
	int		i;
	int		size;
	int		*pipefd;
	t_pipes	*current;
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