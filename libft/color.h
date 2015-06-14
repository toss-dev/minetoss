/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 12:50:27 by rpereira          #+#    #+#             */
/*   Updated: 2015/04/01 16:12:21 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define C_CLEAR ("\033[H\033[2J")
# define C_RESET ("\033[0m")
# define C_BOLD ("\033[1m")
# define C_REV ("\033[7m")
# define C_RESET ("\033[0m")
# define C_WHITE ("\x1B[0m")
# define C_RED ("\x1B[31m")
# define C_GREEN ("\x1B[32m")
# define C_YELLOW ("\x1B[33m")
# define C_BLUE ("\x1B[34m")
# define C_MAGENTA ("\x1B[35m")
# define C_CYAN ("\x1B[36m")
# define C_GRAY ("\033[22;37m")

# define C_LENGTH 4

# define C_BWHITE ("\033[1m\x1B[0m")
# define C_BRED ("\033[1m\x1B[31m")
# define C_BGREEN ("\033[1m\x1B[32m")
# define C_BYELLOW ("\033[1m\x1B[33m")
# define C_BBLUE ("\033[1m\x1B[34m")
# define C_BMAGENTA ("\033[1m\x1B[35m")
# define C_BCYAN ("\033[1m\x1B[36m")
# define C_BGRAY ("\033[1m\033[22;37m")

#endif
