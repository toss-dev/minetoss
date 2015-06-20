/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 03:08:21 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/05 03:08:21 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
**	Generate key to be hash by the hashmap
*/
void	generateTerrainKey(char *buffer, t_point3 index)
{
	sprintf(buffer, "%d:%d:%d", index.x, index.y, index.z);
}

/**
**	return chunk index (x ; z) from the given real world coordinates
*/
t_point3	getTerrainIndexForPos(t_vec3 pos)
{
	t_point3	index;

	if (pos.x < 0)
	{
		pos.x -= TERRAIN_SIZEX;
	}
	if (pos.y < 0)
	{
		pos.y -= TERRAIN_SIZEY;
	}
	if (pos.z < 0)
	{
		pos.z -= TERRAIN_SIZEZ;
	}
	index.x = (int)pos.x / TERRAIN_SIZEX;
	index.y = (int)pos.y / TERRAIN_SIZEY;
	index.z = (int)pos.z / TERRAIN_SIZEZ;
	return (index);
}

t_point3	getTerrainRelativePos(t_vec3 vec)
{
	t_point3	pos;

	pos.x = (int)vec.x % TERRAIN_SIZEX;
	pos.y = (int)vec.y % TERRAIN_SIZEY; 
	pos.z = (int)vec.z % TERRAIN_SIZEZ;
	if (pos.x < 0)
	{
		pos.x += TERRAIN_SIZEX;
	}
	if (pos.y < 0)
	{
		pos.y += TERRAIN_SIZEY;
	}
	if (pos.z < 0)
	{
		pos.z += TERRAIN_SIZEZ;
	}
	//printf("%f %f %f == %d %d %d\n", vec.x ,vec.y, vec.z, pos.x ,pos.y, pos.z);
	return (pos);
}

int			getTerrainHeightAt(t_terrain *terrain, float x, float z)
{
	t_point3	pos;

	pos = getTerrainRelativePos(new_vec3(x, TERRAIN_SIZEY - 1, z));
	while (pos.y > 0)
	{
		if (terrain->blocks[pos.x][pos.y][pos.z] != BLOCK_AIR)
		{
			return (pos.y);
		}
		--pos.y;
	}
	return (0);
}

/**
**	get the terrain in the given position
*/
t_terrain	*getTerrainAt(t_world *world, t_vec3 vec)
{
	t_point3	index;
	char		key[64];

	index = getTerrainIndexForPos(vec);
	generateTerrainKey(key, index);
	return (htab_get(world->terrains, key));
}

t_terrain	*getTerrain(t_world *world, t_point3 index)
{
	char	key[64];

	generateTerrainKey(key, index);
	return (htab_get(world->terrains, key));
}

/**
**	return block at given world position
*/
unsigned		getBlock(t_world *world, t_vec3 vec)
{
	t_terrain	*terrain;
	t_point3	pos;

	terrain = getTerrainAt(world, vec);
	if (terrain == NULL)
	{
		return (BLOCK_AIR);
	}
	pos = getTerrainRelativePos(vec);
	return (terrain->blocks[pos.x][pos.y][pos.z]);
}


void	terrainSetState(t_terrain *terrain, unsigned state)
{
	terrain->state = terrain->state | state;
}

void	terrainUnsetState(t_terrain *terrain, unsigned state)
{
	terrain->state = terrain->state & ~(state);
}

int		terrainHasState(t_terrain *terrain, unsigned state)
{
	return (terrain->state & state);
}

