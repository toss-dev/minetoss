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

void	initTimer(t_timer *timer)
{
	timer->speed = 1;
	timer->tick_ratio = 0;
	timer->ticks = 0;
}

void	updateTimer(t_timer *timer)
{
	static double	last = 0;
	double			current;

	if (timer->ticks >= TICK_PER_CYCLE)
	{
		timer->ticks = timer->ticks % (int)TICK_PER_CYCLE;
	}
	else
	{
		current = glfwGetTime();
		if (current - last >= SECOND_PER_TICK)
		{
			timer->ticks += (current - last) / SECOND_PER_TICK;
			last = current;
		}
	}
	timer->tick_ratio = timer->ticks / (float)TICK_PER_CYCLE;
}

float	getTimeRatio(t_game *game)
{
	return (game->timer.speed);
}
