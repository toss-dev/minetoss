/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 11:42:21 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/06 22:43:43 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

/*
static void		generateTerrainCaves(t_terrain *terrain, float layerF, float weight)
{
    float       ys[TERRAIN_SIZEX][TERRAIN_SIZEY][TERRAIN_SIZEZ];
    int         i;
    t_point3    iter;
    t_vec3      worlditer;

    memset(ys, 0, sizeof(ys));
    for (i = 0 ; i < 3 ; i++)
    {
        for (iter.y = 0 ; iter.y < TERRAIN_SIZEY ; iter.y++)
        {
            for (iter.x = 0 ; iter.x < TERRAIN_SIZEX ; iter.x++)
            {
            	for (iter.z = 0 ; iter.z < TERRAIN_SIZEZ ; iter.z++)
            	{
                    worlditer.x = terrain->index.x * TERRAIN_SIZEX + iter.x;
                    worlditer.y = terrain->index.y * TERRAIN_SIZEY + iter.y;
            		worlditer.z = terrain->index.z * TERRAIN_SIZEZ + iter.z;
            		ys[iter.x][iter.y][iter.z] += noise3(vec3_multiply(worlditer, layerF)) * weight;
                }
            }
        }
        layerF *= 3.5f;
        weight *= 0.5f;
    }

    for (iter.y = 0 ; iter.y < TERRAIN_SIZEY ; iter.y++)
    {
        for (iter.x = 0 ; iter.x < TERRAIN_SIZEX ; iter.x++)
        {
            for (iter.z = 0 ; iter.z < TERRAIN_SIZEZ ; iter.z++)
            {
                if (ys[iter.x][iter.y][iter.z] < 0)
                {
                    terrain->blocks[iter.x][iter.y][iter.z] = BLOCK_STONE;
                }
            }
        }
    }
}*/

static void     generateTerrainSurface(t_terrain *terrain, float layerF, float weight)
{
    float       ys[TERRAIN_SIZEX][TERRAIN_SIZEZ];
    int         i;
    t_point3    iter;
    t_vec2      worldpos;

    for (iter.x = 0 ; iter.x < TERRAIN_SIZEX ; iter.x++)
    {
        for (iter.z = 0 ; iter.z < TERRAIN_SIZEZ ; iter.z++)
        {
            worldpos.x = terrain->index.x * TERRAIN_SIZEX + iter.x;
            worldpos.y = terrain->index.z * TERRAIN_SIZEZ + iter.z;
            ys[iter.x][iter.z] = noise2(vec2_multiply(worldpos, layerF)) * weight;
        }
    }

    for (iter.x = 0 ; iter.x < TERRAIN_SIZEX ; iter.x++)
    {
        for (iter.z = 0 ; iter.z < TERRAIN_SIZEZ ; iter.z++)
        {
            ys[iter.x][iter.z] = clamp(ys[iter.x][iter.z], -0.9f, 0.9f);
            iter.y = CHUNK_BASE_HEIGHT + ys[iter.x][iter.z] * CHUNK_ROUGHNESS;
            terrain->blocks[iter.x][iter.y][iter.z] = BLOCK_GRASS;
            i = rand() % 4 + 4;
            while (i && iter.y > 2)
            {
                --iter.y;
                terrain->blocks[iter.x][iter.y][iter.z] = BLOCK_DIRT;
                --i;
            }
            while (iter.y >= 0)
            {
                terrain->blocks[iter.x][iter.y][iter.z] = BLOCK_STONE;
                iter.y--;
            }
        }
    }
}

void    loadWorldGenerator(void)
{
    srand(time(NULL));
    prepareNoise();
}

/** main terrain generation for terrain at height 0 */
void    generateTerrain(t_terrain *terrain)
{
    terrainSetState(terrain, TERRAIN_GENERATED);
    if (terrain->index.y == 0)
    {
        generateTerrainSurface(terrain, 0.005f, 1.0f);
    }
}
