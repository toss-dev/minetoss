/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 21:03:18 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/09 21:06:22 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

static size_t	getCurrentTimestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

/** prepare the timer */
void	initTimer(t_timer *timer)
{
	timer->last_time = getCurrentTimestamp();
	timer->current_time = 0;
	timer->ratio = 0;
}

/** get the current day ratio [0.0f, 1.0f], see timer.h defines */
float	getTimerDayRatio(t_timer *timer)
{
	return (timer->ratio);
}

/**
**	update the timer so the timer->tick_ratio is in range of [0.0f, 1.0f]
**	and correspond to the current day time
*/
void	updateTimer(t_timer *timer)
{
	size_t	now;

	now = getCurrentTimestamp();
	timer->current_time += (now - timer->last_time);
	if (timer->current_time >= TIME_PER_DAY)
	{
		timer->current_time = timer->current_time % TIME_PER_DAY;
	}
	timer->ratio = timer->current_time / (float)TIME_PER_DAY;
	timer->last_time = now;
}
