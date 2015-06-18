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

#include "main.h"

bool	isGameRunning(t_game *game)
{
	return (game->state & GAME_STATE_RUNNING);
}

void	gameStop(t_game *game)
{
	game->state = game->state & ~(GAME_STATE_RUNNING);
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
	initWindow(&(game->window));
	initEvent(&(game->window));
	initRenderer(&(game->renderer));
	initWorld(&(game->world));
	initTimer(&(game->timer));
	initSound();
	glhCheckError("Game initialization");
	return (game);
}
