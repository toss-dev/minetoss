/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 20:57:07 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/09 20:57:08 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TIMER_H
# define TIMER_H

# define MINUTES_PER_CYCLE	(2)	//time in minute for a cycle (day + night)
# define TIME_PER_DAY 		((int)(MINUTES_PER_CYCLE * 60 * 1000000))

# define NIGHT_END 0.0f
# define DAY_START 0.10f
# define DAY_END 0.50f
# define NIGHT_START 0.60f

typedef struct 	s_timer
{
	size_t	last_time;
	size_t	current_time;
	float 	ratio;
}				t_timer;

void 	initTimer(t_timer *timer);
void	updateTimer(t_timer *timer);
float	getTimerDayRatio(t_timer *timer);

#endif
