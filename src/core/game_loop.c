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

#include "main.h"

static void	updateDebug(t_game *game)
{
	char	buffer[512];

	sprintf(buffer, "x:%f | y:%f | z:%f ; x:%f | y:%f | z:%f",
		game->renderer.camera.pos.x, game->renderer.camera.pos.y, game->renderer.camera.pos.z,
		game->renderer.camera.look_vec.x, game->renderer.camera.look_vec.y, game->renderer.camera.look_vec.z);
	glfwSetWindowTitle(game->window.ptr, buffer);
}

void		gameLoop(t_game *game)
{
	double	prev;

	game->state = game->state | GAME_STATE_RUNNING;
	startThread(game, THRD_GENERATOR, 60, updateWorldGenerator);
	while (!glfwWindowShouldClose(game->window.ptr))
	{
		prev = glfwGetTime();
		updateTimer(&(game->timer));
		updateCamera(&(game->renderer.camera));
		updateWeather(&(game->world), &(game->renderer), &(game->timer));
		updateSound(&(game->sound_manager), &(game->renderer.camera));
		render(&(game->world), &(game->renderer));
		glfwSwapBuffers(game->window.ptr);
		glfwPollEvents();
		glhCheckError("main thread loop");
		game->renderer.fps = (unsigned int)(1 / (glfwGetTime() - prev));
		updateDebug(game);
	}
}
