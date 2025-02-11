/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:18:56 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 16:30:49 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"

/*
** Return 1 if c is alphanumeric
** 0 if not
*/
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
