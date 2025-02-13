/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:27:49 by ygille            #+#    #+#             */
/*   Updated: 2025/02/13 16:21:03 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# define E_SPLIT		"Error : split failed"
# define E_NOFILE		" : no such file or directory : "
# define E_COMMANDNF	" : command not found"
# define E_MALLOC		"Error : malloc failed"
# define E_FORK			"Error : fork failed"
# define E_TMARGS		"Error : too many arguments"
# define E_OPENFILE		"Error : can't open file"
# define E_PIPE			"Error : pipe fail"
# define E_CLOSE		"Error : close fail"
# define E_WAITPID		"Error : waipid fail"
# define E_DUP			"Error : dup fail"
# define E_DUP2			"Error : dup2 fail"
# define E_OPEN			"Error : open fail"

#endif