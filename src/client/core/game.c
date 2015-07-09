/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/14 14:02:06 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/14 14:02:15 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

int	isGameRunning(t_game *game)
{
	return (game->state & GAME_STATE_RUNNING);
}

t_game	*gameNew(void)
{
	t_game	*game;

	logger_log(LOG_FINE, "Creating new game ...");
	if ((game = malloc(sizeof(t_game))) == NULL)
	{
		logger_log(LOG_FINE, "Not enough memory for game.");
		return (NULL);
	}
	memset(game, 0, sizeof(t_game));

	initWorld(&(game->world));
	initTimer(&(game->timer));
	initNetwork(game);

	initWindow(&(game->window));
	initEvent(&(game->window));
	initRenderer(&(game->renderer));
	
	initSound(&(game->sound_manager));
	game->world.timer = &(game->timer);
	game->renderer.timer = &(game->timer);

	glhCheckError("Game initialization");
	return (game);
}
