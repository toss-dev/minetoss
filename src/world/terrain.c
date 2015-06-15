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

#include "main.h"

/**
**	create a chunk instance and add it to the world chunk hashmap
**	generate it and creat it mesh
**
**	return a `t_chunk` pointer to the inserted chunk
*/
t_terrain	*createNewTerrain(t_world *world, t_point3 index)
{
	char		key[64];
	t_terrain	terrain;
	unsigned	i;

	terrain.index = index;
	terrain.state = 0;
	if (index.y != 0)
	{
		terrainSetState(&terrain, TERRAIN_GENERATED);
	}
	for (i = 0 ; i < MESH_PER_TERRAIN ; i++)
	{
		terrain.meshes[i] = new_mesh();
	}
	generateTerrainKey(key, index);
	memset(terrain.blocks, 0, sizeof(terrain.blocks));
	return (htab_insert(world->terrains, key, &terrain, sizeof(t_terrain)));
}

/** called on initialization */
void		loadTerrains(t_world *world)
{
	loadWorldGenerator();
	(void)world;
}

void 		removeTerrain(t_world *world, t_point3 index)
{
	char	key[64];

	generateTerrainKey(key, index);
	htab_remove(world->terrains, key);
}

static void	updateTerrain(t_terrain *terrain, t_world *world)
{
	unsigned	meshID;

	if (!terrainHasState(terrain, TERRAIN_LOADED))
	{
		return ;
	}

	for (meshID = 0 ; meshID < MESH_PER_TERRAIN ; meshID++)
	{
		updateMesh(world, terrain, meshID);
	}
}

static void updateTerrainLoad(t_world *world, t_vec3 vec)
{
	t_terrain	*terrain;
	t_point3	index;
	t_point3	pos;
	int			x;
	int 		z;
	double		dist;

	pos = getTerrainIndexForPos(vec);
	for (x = -CHUNK_RENDER_DISTANCE ; x < CHUNK_RENDER_DISTANCE ; x++)
	{
		for (z = -CHUNK_RENDER_DISTANCE ; z < CHUNK_RENDER_DISTANCE ; z++)
		{
			index.x = pos.x + x;
			index.y = 0;
			index.z = pos.z + z;
			dist = point3_dist(pos, index);
			if (dist < CHUNK_RENDER_DISTANCE)
			{
				terrain = getTerrain(world, index);
				if (terrain == NULL)
				{
					terrain = createNewTerrain(world, index);
				}
				if (!terrainHasState(terrain, TERRAIN_GENERATED))
				{
					generateTerrain(terrain);
				}
				loadTerrain(terrain);
			}
		}
	}
}

/** update and generate terrain at the given pos in the given world */
void	updateTerrains(t_world *world, t_vec3 pos)
{
	updateTerrainLoad(world, pos);
	htab_iter(world->terrains, (t_iter_function)updateTerrain, world);
}