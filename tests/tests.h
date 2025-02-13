/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:24 by ygille            #+#    #+#             */
/*   Updated: 2025/02/12 18:00:28 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "minishell.h"
# include "ft_printf.h"

int		launch_all(char **envp);
char	**init_list(void);
int		launch_test(int fd[2], char *test, char **envp);
int		launch_ref(int fd[2], char *test, char **envp);

void	launch_one(char *test, char **envp);
void	launch_diff(char **envp);
void	launch_loop(char *test, char **envp);

#endif