/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:41 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 14:28:35 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Init and launch a loop
** waiting for user input
*/
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	minishell;

	define_mode(&minishell, argc, argv);
	init_minishell(&minishell, envp);
	while (1)
	{
		line = get_line(&minishell);
		parse_line(&minishell, line);
		update_infos(&minishell);
	}
	return (0);
}

/*
** Detect if we are in interact mode, non-interact mode
** or script mode, in this case open the file
*/
void	define_mode(t_minishell *minishell, int argc, char **argv)
{
	if (argc > 2)
		return (error(E_TMARGS));
	if (argc == 2)
	{
		minishell->mode = SCRIPT_MODE;
		minishell->input_file = open(argv[1], O_RDONLY);
		if (minishell->input_file == -1)
			return (error(E_OPENFILE));
	}
	else if (isatty(STDIN_FILENO))
		minishell->mode = TTY_MODE;
	else
	{
		minishell->mode = NO_TTY_MODE;
		minishell->input_file = STDIN_FILENO;
	}
}

/*
** Minishell get_next_line
** use gnl if we are in script or non interact mode
** use readline if in interact mode
*/
char	*get_line(t_minishell *minishell)
{
	char	*line;
	char	*tmp;

	if (minishell->mode == TTY_MODE)
		return (readline(minishell->prompt));
	line = get_next_line(minishell->input_file);
	if (line)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
	}
	return (line);
}

/*
** Function to display an error message and exit the program
*/
void	error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

/*
** Free args and exit the program
*/
void	free_exit(t_minishell *minishell, char **args, char *message)
{
	garbage_destroy(minishell);
	free_struct(minishell);
	free_split(&args);
	rl_clear_history();
	if (minishell->mode == SCRIPT_MODE)
		close (minishell->input_file);
	if (message)
		error(message);
	if (minishell->mode != TTY_MODE)
		exit(minishell->last_return_value);
	exit(EXIT_SUCCESS);
}
