/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/23 12:05:50 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/02 23:11:04 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include "libft.h"
# include <time.h>

enum	e_log_level
{
	LOG_DEFAULT,
	LOG_FINE,
	LOG_WARNING,
	LOG_ERROR
};

typedef struct 	s_logger_format
{
	char	str[8];
	char	color[16];
}				t_logger_format;

void	logger_log(int level, char *str, ...);

#endif
