/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:54:08 by ygille            #+#    #+#             */
/*   Updated: 2025/01/28 19:57:57 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_text(char *text, char format[5], char color[6])
{
	ft_putstr_fd(format, 1);
	ft_putstr_fd(color, 1);
	ft_putendl_fd(text, 1);
	ft_putstr_fd(TEXT_RESET, 1);
}
