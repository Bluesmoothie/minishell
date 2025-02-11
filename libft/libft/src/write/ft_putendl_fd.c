/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:26:08 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 17:59:09 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_write.h"

/*
** Write s to fd terminating with \n
*/
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd (s, fd);
	write (fd, "\n", 1);
}
