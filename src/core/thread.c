/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/14 13:20:05 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/14 13:20:09 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	updateThread(t_thread_param *params)
{
	unsigned int	t;
	double			prev;
	unsigned int	took;

	logger_log(LOG_FINE, "Starting thread: %u (%p)", params->threadID, params);
	t = 1000000 / params->ups;
	while (isGameRunning(params->game))
	{
		prev = glfwGetTime();
		params->callback(params->game);
		took = (glfwGetTime() - prev) * 1000000;
		if (took < t)
		{
			usleep(t - took);
		}
	}
	logger_log(LOG_FINE, "Stopping thread: %u (%p)", params->threadID, params);
	free(params);
	thrd_exit(EXIT_SUCCESS);
}

/**
**	start a new thread pointing to the given thrd_t pointer
**
**	it will loop on the given callback at `ups` update per seconds
**	the loop will stop when `callbackstop` function will something different from 0
*/
void	startThread(t_game *game, unsigned threadID, unsigned ups, t_thread_callback callback)
{
	t_thread_param	*params;

	if ((params = (t_thread_param*)malloc(sizeof(t_thread_param))) == NULL)
	{
		logger_log(LOG_ERROR, "Not enough memory to create thread: %u\n", threadID);
		return ;
	}
	params->game = game;
	params->threadID = threadID;
	params->ups = ups;
	params->callback = callback;
	if (thrd_create(game->threads + threadID, (thrd_start_t)updateThread, params) != thrd_success)
	{
		free(params);
		logger_log(LOG_ERROR, "Thread couldnt be created: %u\n", threadID);
		return ;
	}
}
