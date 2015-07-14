/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/14 14:10:28 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/14 14:10:31 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

/**	update the timer, camera, sounds and render */
static void	updateGame(t_game *game)
{
	updateTimer(&(game->timer));
	updateCamera(&(game->renderer.camera));
	updateWeather(&(game->world), &(game->renderer), &(game->timer));
	updateSound(&(game->sound_manager), &(game->renderer.camera));
}

static void	renderGame(t_game *game)
{
	render(game);
	glfwSwapBuffers(game->window.ptr);
	glfwPollEvents();
}

void		gameLoop(t_game *game)
{
	double	prev;

	gameSetState(game, GAME_RUNNING);
	gameSetState(game, GAME_INGAME);
	rendererAddView(&(game->renderer), VIEW_MAIN_MENU);

	startNetwork(game);
	startTerrainMesher(game);

	while (!glfwWindowShouldClose(game->window.ptr))
	{
		prev = glfwGetTime();
		updateGame(game);
		renderGame(game);
		game->renderer.fps = (unsigned int)(1 / (glfwGetTime() - prev));
		usleep(1000000 / 120);
	}
}
