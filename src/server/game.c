/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/main.h"

int 	isGameRunning(t_game *game)
{
	return (game->state & GAME_STATE_RUNNING);
}

void	gameInit(t_game *game)
{
	(void)game;
	logger_log(LOG_FINE, "Initializing game");
}

/** main server loop for updates */
void	gameLoop(t_game *game)
{
	logger_log(LOG_FINE, "Starting loop");
	while (isGameRunning(game))
	{
		srvTick(game->server);
		usleep(1000000 / 60);
	}
}

void	gameStart(t_game *game)
{
	game->state = game->state | GAME_STATE_RUNNING;
	logger_log(LOG_FINE, "Starting network");
	networkStart(game);
}

void	gameStop(t_game *game)
{
	game->state = game->state & ~(GAME_STATE_RUNNING);

	unsigned	i;
	for (i = 0 ; i < THRD_MAX ; ++i)	//wait for each thread to exit
	{
		pthread_join(game->threads[i], NULL);
	}

	networkStop(game);
	free(game);
	exit(EXIT_SUCCESS);
}
