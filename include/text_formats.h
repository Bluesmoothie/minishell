/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_formats.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:46:39 by ygille            #+#    #+#             */
/*   Updated: 2025/03/03 17:41:28 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_FORMATS_H
# define TEXT_FORMATS_H

# define TEXT_BLACK			"\033[30m"
# define TEXT_RED	 		"\033[31m"
# define TEXT_GREEN	 		"\033[32m"
# define TEXT_YELLOW		"\033[33m"
# define TEXT_BLUE			"\033[34m"
# define TEXT_MAGENTA		"\033[35m"
# define TEXT_CYAN			"\033[36m"
# define TEXT_WHITE			"\033[37m"
# define TEXT_NULL_COLOR	"\0\0\0\0\0\0"
# define TEXT_BOLD			"\033[1m"
# define TEXT_DIM			"\033[2m"
# define TEXT_ITALIC		"\033[3m"
# define TEXT_UNDERLINED	"\033[4m"
# define TEXT_BLINK			"\033[5m"
# define TEXT_REVERSE		"\033[7m"
# define TEXT_HIDDEN		"\033[8m"
# define TEXT_RESET			"\033[0m"
# define TEXT_NULL_FORMAT	"\0\0\0\0\0"

# define PROMPT_LEFT_COLOR		TEXT_GREEN
# define PROMPT_RIGHT_COLOR		TEXT_MAGENTA

#endif