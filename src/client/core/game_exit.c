/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/14 14:10:36 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/14 14:10:42 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

static void	cleanRenderer(t_renderer *renderer)
{
	unsigned int i;

	for (i = 0 ; i < VIEW_MAX ; i++)
	{
		viewDestroy(renderer->views + i);
	}
	skyDelete(&(renderer->sky));
	modelDelete(&(renderer->quad_model));
	unloadFont();
}

static void deleteTerrain(t_terrain *terrain)
{
	unsigned	i;

	for (i = 0 ; i < MESH_PER_TERRAIN ; i++)
	{
		modelDelete(terrain->meshes + i);
	}
}

static void	cleanWorld(t_world *world)
{
	htab_delete(&(world->terrains), deleteTerrain);
}

void	gameExit(t_game *game)
{
	gameUnsetState(game, GAME_RUNNING);

	stopNetwork(game);

	unsigned	i;
	for (i = 0 ; i < THRD_MAX ; i++)	//wait for each thread to exit
	{
		pthread_join(game->threads[i], NULL);
	}
	cleanWindow(&(game->window));
	cleanRenderer(&(game->renderer));
	cleanWorld(&(game->world));
	cleanBlocks(game->renderer.blocks);
	alhStop(&(game->sound_manager));
	exit(EXIT_SUCCESS);
}
