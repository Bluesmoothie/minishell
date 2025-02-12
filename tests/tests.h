/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:24 by ygille            #+#    #+#             */
/*   Updated: 2025/02/12 15:10:48 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "minishell.h"
# include "ft_printf.h"

char	**init_list(void);
int		launch_test(int fd[2], char *test, char **envp);
int		launch_ref(int fd[2], char *test, char **envp);

#endif