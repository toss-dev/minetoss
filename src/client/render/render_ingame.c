/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ingame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 23:19:25 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/12 18:03:40 by rpereira         ###   ########.fr       */
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

void	renderIngame(t_game *game)
{
	t_world		*world;
	t_renderer	*renderer;

	world = &(game->world);
	renderer = &(game->renderer);

	renderSky(world, renderer);
	renderTerrains(world, renderer);
	updateDebug(game);
}