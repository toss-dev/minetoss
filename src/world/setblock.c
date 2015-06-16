/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setblock     .c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 03:08:21 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/05 03:08:21 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	toggleMeshUpdate(t_terrain *terrain, unsigned meshID)
{
	modelUnsetState(terrain->meshes + meshID, MODEL_VERTICES_UP_TO_DATE);
}

/** update chunks near to the block at `pos` (at chunk `meshID` into the given `terrain` which has just changed */
static void	updateChunksMesh(t_world *world, t_terrain *terrain, t_point3 pos, unsigned meshID)
{
	t_terrain	*tmp;

	modelUnsetState(terrain->meshes + meshID, MODEL_VERTICES_UP_TO_DATE);

	/** below chunk in the same terrain need update */
	if (pos.y % MESH_SIZEY == 0)
	{
		if (meshID == 0 && (tmp = getTerrain(world, new_point3(terrain->index.x, terrain->index.y - 1, terrain->index.z))) != NULL)
		{
			toggleMeshUpdate(tmp, MESH_PER_TERRAIN - 1);
		}
		else
		{
			toggleMeshUpdate(terrain, meshID - 1);
		}
	}

	/** upper chunk in the same terrain need update */
	if (pos.y % MESH_SIZEY == MESH_SIZEY - 1)
	{
		if (meshID == MESH_PER_TERRAIN - 1 && (tmp = getTerrain(world, new_point3(terrain->index.x, terrain->index.y + 1, terrain->index.z))) != NULL)
		{
			toggleMeshUpdate(tmp, 0);
		}
		else
		{
			toggleMeshUpdate(terrain, meshID + 1);
		}
	}

	/** same chunk in the left terrain need update */
	if (pos.x == 0)
	{
		if ((tmp = getTerrain(world, new_point3(terrain->index.x - 1, terrain->index.y, terrain->index.z))) != NULL)
		{
			toggleMeshUpdate(tmp, meshID);
		}
	}

	/** same chunk in the right terrain need update */
	if (pos.x == TERRAIN_SIZEX - 1)
	{
		if ((tmp = getTerrain(world, new_point3(terrain->index.x + 1, terrain->index.y, terrain->index.z))) != NULL)
		{
			toggleMeshUpdate(tmp, meshID);
		}
	}

	/** same chunk in the front terrain need update */
	if (pos.z == 0)
	{
		if ((tmp = getTerrain(world, new_point3(terrain->index.x, terrain->index.y, terrain->index.z - 1))) != NULL)
		{
			toggleMeshUpdate(tmp, meshID);
		}
	}

	/** same chunk in the back terrain need update */
	if (pos.z == TERRAIN_SIZEZ - 1)
	{
		if ((tmp = getTerrain(world, new_point3(terrain->index.x, terrain->index.y, terrain->index.z + 1))) != NULL)
		{
			toggleMeshUpdate(tmp, meshID);
		}
	}
}

/**
**	set block at given position
*/
void 			setBlock(t_world *world, unsigned blockID, t_vec3 vec)
{
	t_terrain	*terrain;
	t_point3	pos;
	unsigned	meshID;

	terrain = getTerrainAt(world, vec);
	if (terrain == NULL)
	{
		terrain = createNewTerrain(world, getTerrainIndexForPos(vec));
		loadTerrain(terrain);
		logger_log(LOG_FINE, "Created a new terrain when placing block (at %d:%d:%d)", terrain->index.x, terrain->index.y, terrain->index.z);
	}
	pos = getTerrainRelativePos(vec);
	terrain->blocks[pos.x][pos.y][pos.z] = blockID;
	meshID = pos.y / MESH_SIZEY;
	
	updateChunksMesh(world, terrain, pos, meshID);
}