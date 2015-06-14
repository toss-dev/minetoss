/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/23 11:53:09 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/09 19:38:07 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"

void		logger_log(int level, char *str, ...)
{
	static t_logger_format format[5] = {
		{"INFO", ""},
		{"FINE", C_GREEN},
		{"WARNING", C_BYELLOW},
		{"ERROR", C_BRED}
	};
	char		buffer[1024];
	time_t		now;
	struct tm	*t;
	va_list		arg;

	now = time(0);
	t = localtime(&now);

	va_start(arg, str);
	vsprintf(buffer, str, arg);
	va_end(arg);

	printf("%s[%d:%d:%d] [%s]%s %s\n", format[level].color, t->tm_hour, t->tm_min, t->tm_sec, format[level].str, C_RESET, buffer);
	fflush(stdout);
}
