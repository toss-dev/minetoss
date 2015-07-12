/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 02:28:42 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/03 02:39:40 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

/**
**	A terrain is a strcture, which contains:
**		- a TERRAIN_SIZE_X * TERRAIN_SIZE_Y * TERRAIN_SIZE_Z array of blocks
**		- a point3 indices in the world (eg., (0;0;0))
**		- MESHES_PER_TERRAIN model which are rendered by the terrain rendered if needed
**		(basically, theses are the blocks meshes)
**
**
**	If a terrain has the state `TERRAIN_LOADED`, the terrain is updated on every loop
**	else way, it is added to a `garbage list`.
**	At the end of a world update, every terrain in this garbage list are removed (freed)
*/



/**
**	create a chunk instance and add it to the world chunk hashmap
**	generate it and creat it mesh
**
**	return a `t_chunk` pointer to the inserted chunk
*/
t_terrain	*createNewTerrain(t_world *world, t_point3 index)
{
	char		key[64];
	t_terrain	buffer;
	unsigned	i;
	t_terrain	*terrain;

	buffer.index = index;
	buffer.state = 0;
	for (i = 0 ; i < MESH_PER_TERRAIN ; i++)
	{
		buffer.meshes[i] = new_model(GL_STREAM_DRAW);
	}
	generateTerrainKey(key, index);
	memset(buffer.blocks, 0, sizeof(buffer.blocks));
	terrain = htab_insert(world->terrains, key, &buffer, sizeof(t_terrain));
	updateTerrainNeighborMeshesData(world, terrain);
	return (terrain);
}

/** called on initialization */
void	loadTerrains(t_world *world)
{
	loadWorldGenerator();
	(void)world;
}

void 	removeTerrain(t_world *world, t_point3 index)
{
	array_list_add(&(world->terrain_garbage), &index);
}

/** set the terrainas loaded, which mean it will be updated */
void 	loadTerrain(t_terrain *terrain)
{
	terrainSetState(terrain, TERRAIN_LOADED);
}

/** unload the terrani, which mean it isnt updated no more and added to the garbage collector */
void 	unloadTerrain(t_terrain *terrain)
{
	terrainUnsetState(terrain, TERRAIN_LOADED);
}

static void	updateTerrain(t_world *world, t_terrain *terrain)
{
	if (terrainHasState(terrain, TERRAIN_LOADED))
	{
		t_point3	pos;
		double		dist;
		int			meshID;

		pos = getTerrainIndexForPos(g_game->renderer.camera.pos);
		dist = point3_dist(pos, terrain->index);
		if (dist >= TERRAIN_KEEP_LOAD_DISTANCE)
		{
			unloadTerrain(terrain);
			return ;
		}

		for (meshID = 0 ; meshID < MESH_PER_TERRAIN ; meshID++)
		{
			updateMeshes(world, terrain, meshID);
		}
	}
	else
	{
		removeTerrain(world, terrain->index);
	}
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

static void	removeTerrainAt(t_world *world, t_point3 index)
{
	char	key[64];

	generateTerrainKey(key, index);
	htab_remove_key(world->terrains, key, deleteTerrain);
}

/** update and generate terrain at the given pos in the given world */
void		updateTerrains(t_world *world)
{
	HTAB_ITER_START(world->terrains, t_terrain, terrain);
	{
		updateTerrain(world, terrain);
	}
	HTAB_ITER_END(world->terrains, t_terrain, terrain);


	ARRAY_LIST_ITER_START(world->terrain_garbage, t_point3, index, i);
	{
		removeTerrainAt(world, new_point3(index->x, index->y, index->z));
	}
	ARRAY_LIST_ITER_END(world->terrain_garbage, t_point3, index, i);

	array_list_clear(&(world->terrain_garbage));
}
