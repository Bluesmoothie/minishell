/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   public_get_next_line.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:13 by ygille            #+#    #+#             */
/*   Updated: 2025/02/07 20:00:06 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUBLIC_GET_NEXT_LINE_H
# define PUBLIC_GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"

char	*get_next_line(int fd);

#endif