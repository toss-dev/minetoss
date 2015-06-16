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

#include "main.h"

static void	cleanRenderer(t_renderer *renderer)
{
	skyDelete(&(renderer->sky));
	modelDelete(&(renderer->quad_model));
}

static void deleteTerrain(t_terrain *terrain)
{
	unsigned	i;

	for (i = 0 ; i < MESH_PER_TERRAIN ; i++)
	{
		modelDelete(terrain->meshes + i);
	}
	free(terrain);
}

static void	cleanWorld(t_world *world)
{
	htab_delete(&(world->terrains), deleteTerrain);
}

void		gameClean(t_game *game)
{
	unsigned	i;

	for (i = 0 ; i < THRD_MAX ; i++)	//wait for each thread to exit
	{
		thrd_join(game->threads[i], NULL);
	}
	cleanWindow(&(game->window));
	cleanRenderer(&(game->renderer));
	cleanWorld(&(game->world));
	cleanBlocks(game->renderer.blocks);
	exit(EXIT_SUCCESS);
}
