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

int		isGameRunning(t_game *game)
{
	return (gameHasState(game, GAME_RUNNING));
}

int		gameHasState(t_game *game, unsigned int state)
{
	return (game->state & state);
}

void	gameSetState(t_game *game, unsigned int state)
{
	game->state = game->state | state;
}

void	gameUnsetState(t_game *game, unsigned int state)
{
	game->state = game->state & ~(state);
}

t_game	*gameNew(void)
{
	t_game	*game;

	logger_log(LOG_FINE, "Creating new game ...");
	if ((game = (t_game*)malloc(sizeof(t_game))) == NULL)
	{
		logger_log(LOG_FINE, "Not enough memory for game.");
		return (NULL);
	}
	memset(game, 0, sizeof(t_game));

	initWorld(&(game->world));
	initTimer(&(game->timer));

	initWindow(&(game->window));
	initEvent(&(game->window));
	initRenderer(&(game->renderer));
	
	initSound(&(game->sound_manager));
	game->world.timer = &(game->timer);
	game->renderer.timer = &(game->timer);

	glhCheckError("Game initialization");
	return (game);
}
