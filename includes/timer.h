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


#ifndef WORLD_TIME_H
# define WORLD_TIME_H

# define TPS 20											//ticks per seconds (time unit)
# define TIME_PER_CYCLE	2								//time in minute for a cycle (day + night)
# define TICK_PER_CYCLE	(TIME_PER_CYCLE * TPS * 60)		//tick number in a fully day-night cycle
# define SECOND_PER_TICK (1 / (double)TPS)

# define NIGHT_END 		0
# define DAY_START		0.1f
# define DAY_END 		0.5f
# define NIGHT_START	0.6f

typedef struct 	s_timer
{
	float 		speed;
	float 		tick_ratio;
	unsigned	ticks;
}				t_timer;

void 	initTimer(t_timer *timer);
void	updateTimer(t_timer *timer);

#endif
