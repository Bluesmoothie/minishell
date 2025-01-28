/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:41 by ygille            #+#    #+#             */
/*   Updated: 2025/01/28 18:10:33 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tests(void)
{
	char	*line;

	line = readline("minishell$ ");
	ft_putstr_fd(line, 1);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	tests();
	return (0);
}
