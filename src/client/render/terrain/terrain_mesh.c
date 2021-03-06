/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain_mesh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 02:26:08 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/07 18:21:21 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

/** chunk mesh factory */

/* 
		//POINTS:
				 
	      4-----7
         /|    /|
        0-----3 |
        | 5___|_6 
        |/    | /
        1-----2		               		
*/

# define POINT0(X, Y, Z, S) new_vec3(-S + X,  S + Y, -S + Z)
# define POINT1(X, Y, Z, S) new_vec3(-S + X, -S + Y, -S + Z)
# define POINT2(X, Y, Z, S) new_vec3(-S + X, -S + Y,  S + Z)
# define POINT3(X, Y, Z, S) new_vec3(-S + X,  S + Y,  S + Z)
# define POINT4(X, Y, Z, S) new_vec3( S + X,  S + Y, -S + Z)
# define POINT5(X, Y, Z, S) new_vec3( S + X, -S + Y, -S + Z)
# define POINT6(X, Y, Z, S) new_vec3( S + X, -S + Y,  S + Z)
# define POINT7(X, Y, Z, S) new_vec3( S + X,  S + Y,  S + Z)

/*
		UVS (texture):
		0--3
		|  |
		1--2

*/

# define UV0 new_vec2(uv.x, 						uv.y)
# define UV1 new_vec2(uv.x,							uv.y + TEXTURE_UV_HEIGHT_UNIT)
# define UV2 new_vec2(uv.x + TEXTURE_UV_WIDTH_UNIT,	uv.y + TEXTURE_UV_HEIGHT_UNIT)
# define UV3 new_vec2(uv.x + TEXTURE_UV_WIDTH_UNIT,	uv.y)


t_array_list	g_vertex_array;

/** call on program initialiaztion */
void	loadTerrainMeshFactory(t_renderer *renderer)
{
	g_vertex_array = array_list_new(2048, sizeof(t_vertex) * 6);
	(void)renderer;
}

static void toggleLeftFace(t_vertex face_buffer[6], t_vec2 uv, int x, int y, int z, float s)
{
	face_buffer[0] = new_vertex(POINT4(x, y, z, s), new_vec3(0, 0, 1), UV0);
	face_buffer[1] = new_vertex(POINT5(x, y, z, s), new_vec3(0, 0, 1), UV1);
	face_buffer[2] = new_vertex(POINT1(x, y, z, s), new_vec3(0, 0, 1), UV2);
	face_buffer[3] = face_buffer[0];
	face_buffer[4] = face_buffer[2];
	face_buffer[5] = new_vertex(POINT0(x, y, z, s), new_vec3(0, 0, 1), UV3);
}

static void toggleRightFace(t_vertex face_buffer[6], t_vec2 uv, int x, int y, int z, float s)
{
	face_buffer[0] = new_vertex(POINT3(x, y, z, s), new_vec3(0, 0, 1), UV0);
	face_buffer[1] = new_vertex(POINT2(x, y, z, s), new_vec3(0, 0, 1), UV1);
	face_buffer[2] = new_vertex(POINT6(x, y, z, s), new_vec3(0, 0, 1), UV2);
	face_buffer[3] = face_buffer[0];
	face_buffer[4] = face_buffer[2];
	face_buffer[5] = new_vertex(POINT7(x, y, z, s), new_vec3(0, 0, 1), UV3);
}

static void toggleTopFace(t_vertex face_buffer[6], t_vec2 uv, int x, int y, int z, float s)
{
	face_buffer[0] = new_vertex(POINT4(x, y, z, s), new_vec3(0, 1, 0), UV0);
	face_buffer[1] = new_vertex(POINT0(x, y, z, s), new_vec3(0, 1, 0), UV1);
	face_buffer[2] = new_vertex(POINT3(x, y, z, s), new_vec3(0, 1, 0), UV2);
	face_buffer[3] = face_buffer[0];
	face_buffer[4] = face_buffer[2];
	face_buffer[5] = new_vertex(POINT7(x, y, z, s), new_vec3(0, 1, 0), UV3);
}


static void toggleBotFace(t_vertex face_buffer[6], t_vec2 uv, int x, int y, int z, float s)
{
	face_buffer[0] = new_vertex(POINT1(x, y, z, s), new_vec3(0, -1, 0), UV0);
	face_buffer[1] = new_vertex(POINT5(x, y, z, s), new_vec3(0, -1, 0), UV1);
	face_buffer[2] = new_vertex(POINT6(x, y, z, s), new_vec3(0, -1, 0), UV2);
	face_buffer[3] = face_buffer[0];
	face_buffer[4] = face_buffer[2];
	face_buffer[5] = new_vertex(POINT2(x, y, z, s), new_vec3(0, -1, 0), UV3);
}

static void toggleFrontFace(t_vertex face_buffer[6], t_vec2 uv, int x, int y, int z, float s)
{
	face_buffer[0] = new_vertex(POINT0(x, y, z, s), new_vec3(-1, 0, 0), UV0);
	face_buffer[1] = new_vertex(POINT1(x, y, z, s), new_vec3(-1, 0, 0), UV1);
	face_buffer[2] = new_vertex(POINT2(x, y, z, s), new_vec3(-1, 0, 0), UV2);
	face_buffer[3] = face_buffer[0];
	face_buffer[4] = face_buffer[2];
	face_buffer[5] = new_vertex(POINT3(x, y, z, s), new_vec3(-1, 0, 0), UV3);
}

static void toggleBackFace(t_vertex face_buffer[6], t_vec2 uv, int x, int y, int z, float s)
{
	face_buffer[0] = new_vertex(POINT7(x, y, z, s), new_vec3(1, 0, 0), UV0);
	face_buffer[1] = new_vertex(POINT6(x, y, z, s), new_vec3(1, 0, 0), UV1);
	face_buffer[2] = new_vertex(POINT5(x, y, z, s), new_vec3(1, 0, 0), UV2);
	face_buffer[3] = face_buffer[0];
	face_buffer[4] = face_buffer[2];
	face_buffer[5] = new_vertex(POINT4(x, y, z, s), new_vec3(1, 0, 0), UV3);
}

typedef void (*t_face_function)(t_vertex *, t_vec2 , int , int , int, float);

static void toggleCubeFace(t_vertex face_buffer[6], unsigned faceID, t_block *block, t_point3 pos)
{
	static t_face_function	faces[6] = {
		toggleLeftFace,
		toggleRightFace,
		toggleTopFace,
		toggleBotFace,
		toggleFrontFace,
		toggleBackFace
	};
	t_vec2	uv;

	uv = new_vec2(0, block->textureID[faceID] * TEXTURE_UV_HEIGHT_UNIT);
	faces[faceID](face_buffer, uv, pos.x, pos.y, pos.z, 0.5f);
}

static void pushFace(unsigned faceID, t_block *block, t_point3 pos)
{
	t_vertex	face_buffer[6];

	toggleCubeFace(face_buffer, faceID, block, pos);
	array_list_add(&g_vertex_array, face_buffer);
}

/** this functions add every block faces like an idiot for now */
static void addBlockFaces(t_terrain *terrain, t_terrain *neighbor[6], t_block *block, t_point3 pos)
{

/*********************************************************************/

	if ((pos.x == 0 && neighbor[0] && !isBlockVisible(neighbor[0]->blocks[TERRAIN_SIZEX - 1][pos.y][pos.z]))
			|| (pos.x > 0 && !isBlockVisible(terrain->blocks[pos.x - 1][pos.y][pos.z])))
	{
		pushFace(BLOCK_FACE_FRONT, block, pos);
	}

	if ((pos.x == TERRAIN_SIZEX - 1 && neighbor[2] && !isBlockVisible(neighbor[2]->blocks[0][pos.y][pos.z]))
			|| (pos.x < TERRAIN_SIZEX - 1 && !isBlockVisible(terrain->blocks[pos.x + 1][pos.y][pos.z])))
	{
		pushFace(BLOCK_FACE_BACK, block, pos);
	}

/*********************************************************************/



/*********************************************************************/
	if ((pos.y == 0 && neighbor[4] && !isBlockVisible(neighbor[4]->blocks[pos.x][TERRAIN_SIZEY - 1][pos.z]))
			|| (pos.y > 0 && !isBlockVisible(terrain->blocks[pos.x][pos.y - 1][pos.z])))
	{
		pushFace(BLOCK_FACE_BOT, block, pos);
	}

	if ((pos.y == TERRAIN_SIZEY - 1 && !isBlockVisible(neighbor[5]->blocks[pos.x][0][pos.z]))
			|| (pos.y < TERRAIN_SIZEY - 1 && !isBlockVisible(terrain->blocks[pos.x][pos.y + 1][pos.z])))
	{
		pushFace(BLOCK_FACE_TOP, block, pos);
	}
/*********************************************************************/

/*********************************************************************/

	if ((pos.z == 0 && neighbor[1] && !isBlockVisible(neighbor[1]->blocks[pos.x][pos.y][TERRAIN_SIZEZ - 1]))
			|| (pos.z > 0 && !isBlockVisible(terrain->blocks[pos.x][pos.y][pos.z - 1])))
	{
		pushFace(BLOCK_FACE_LEFT, block, pos);
	}

	if ((pos.z == TERRAIN_SIZEZ - 1 && neighbor[3] && !isBlockVisible(neighbor[3]->blocks[pos.x][pos.y][0]))
			|| (pos.z < TERRAIN_SIZEZ - 1 && !isBlockVisible(terrain->blocks[pos.x][pos.y][pos.z + 1])))
	{
		pushFace(BLOCK_FACE_RIGHT, block, pos);
	}

/*********************************************************************/
}

/** push every visible faces to the vertex array list from the given chunk */
static void generateVertexArrayList(t_terrain *terrain, t_terrain *neighbor[6], unsigned meshID)
{
	t_block 	*block;
	unsigned	blockID;
	t_point3	pos;
	int			start;
	int 		end;

	start = meshID * MESH_SIZEY;
	end = start + MESH_SIZEY;
	for (pos.y = start ; pos.y < end ; pos.y++)
	{
		for (pos.x = 0 ; pos.x < TERRAIN_SIZEX ; pos.x++)
		{
			for (pos.z = 0 ; pos.z < TERRAIN_SIZEZ ; pos.z++)
			{
				blockID = terrain->blocks[pos.x][pos.y][pos.z];
				if (isBlockVisible(blockID))
				{
					block = getBlockByID(blockID);
					addBlockFaces(terrain, neighbor, block, pos);
				}
			}	
		}
	}
}

static void getChunkNeighbor(t_world *world, t_terrain *terrain, t_terrain *neighbor[6])
{
	neighbor[0] = getTerrain(world, new_point3(terrain->index.x - 1,	terrain->index.y, terrain->index.z));
	neighbor[1] = getTerrain(world, new_point3(terrain->index.x,		terrain->index.y, terrain->index.z - 1));
	neighbor[2] = getTerrain(world, new_point3(terrain->index.x + 1,	terrain->index.y, terrain->index.z));
	neighbor[3] = getTerrain(world, new_point3(terrain->index.x,		terrain->index.y, terrain->index.z + 1));
	neighbor[4] = getTerrain(world, new_point3(terrain->index.x,		terrain->index.y - 1, terrain->index.z));
	neighbor[5] = getTerrain(world, new_point3(terrain->index.x,		terrain->index.y + 1, terrain->index.z));
}


/**
**	update the mesh at given ID for this terrain
*/
void		updateTerrainMeshData(t_world *world, t_terrain *terrain, unsigned meshID)
{
	t_terrain	*neighbor[6];

	getChunkNeighbor(world, terrain, neighbor);
	generateVertexArrayList(terrain, neighbor, meshID);
	setModelVertices(terrain->meshes + meshID, array_list_to_buffer(g_vertex_array, ARRAY_LIST_RDWR), g_vertex_array.size * 6);
	array_list_clear(&g_vertex_array);
}

/**
**	update every meshes for the given terrain
*/
void		updateTerrainMeshes(t_world *world, t_terrain *terrain)
{
	unsigned	i;

	for (i = 0 ; i < MESH_PER_TERRAIN ; i++)
	{
		updateTerrainMeshData(world, terrain, i);
	}
}

/**
**	update every neighbor chunks
*/
void		updateTerrainNeighborMeshesData(t_world *world, t_terrain *terrain)
{
	t_terrain	*neighbor[6];
	
	getChunkNeighbor(world, terrain, neighbor);
	
	if (neighbor[0])
	{
		updateTerrainMeshes(world, neighbor[0]);
	}

	if (neighbor[1])
	{
		updateTerrainMeshes(world, neighbor[1]);
	}

	if (neighbor[2])
	{
		updateTerrainMeshes(world, neighbor[2]);
	}

	if (neighbor[3])
	{
		updateTerrainMeshes(world, neighbor[3]);
	}

	if (neighbor[4])
	{
		updateTerrainMeshes(world, neighbor[4]);
	}

	if (neighbor[5])
	{
		updateTerrainMeshes(world, neighbor[5]);
	}
}


/**************************************************************************/
