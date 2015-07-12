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

static void	updateDebug(t_game *game)
{
	char	buffer[512];

	sprintf(buffer, "x:%f | y:%f | z:%f ; x:%f | y:%f | z:%f",
		game->renderer.camera.pos.x, game->renderer.camera.pos.y, game->renderer.camera.pos.z,
		game->renderer.camera.look_vec.x, game->renderer.camera.look_vec.y, game->renderer.camera.look_vec.z);
	glfwSetWindowTitle(game->window.ptr, buffer);
	glhCheckError("main thread loop");
}

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
	render(&(game->world), &(game->renderer));
	glfwSwapBuffers(game->window.ptr);
	glfwPollEvents();
}

void		gameLoop(t_game *game)
{
	double	prev;

	game->state = game->state | GAME_STATE_RUNNING;

	startNetwork(game);
	startTerrainMesher(game);

	while (!glfwWindowShouldClose(game->window.ptr))
	{
		prev = glfwGetTime();
		updateGame(game);
		renderGame(game);
		game->renderer.fps = (unsigned int)(1 / (glfwGetTime() - prev));
		updateDebug(game);
		usleep(10000);
	}
}
