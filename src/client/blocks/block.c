/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 00:09:08 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/06 19:37:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

void 		cleanBlocks(t_block *blocks)
{
	unsigned	i;

	for (i = 0 ; i < BLOCK_MAX ; i++)
	{
		free(blocks[i].toString);
	}
}

/**
**	va_args correspond to texture to use for each face
**
**	example usage for dirt : blockCreate(blocks, BLOCK_DIRT,  BLOCK_TEXTURE_DIRT, "dirt", 0)
**	example usage for grass: blockCreate(blocks, BLOCK_GRASS, BLOCK_TEXTURE_DIRT, "grass", 1, BLOCK_FACE_TOP, BLOCK_TEXTURE_GRASS)
*/
static void	blockCreate(t_block *blocks, unsigned id, unsigned textureID, char const *name, unsigned count, ...)
{
	va_list		args;
	unsigned 	i;
	unsigned	faceID;

	blocks[id].id = id;
	blocks[id].textureID[0] = textureID;
	blocks[id].textureID[1] = textureID;
	blocks[id].textureID[2] = textureID;
	blocks[id].textureID[3] = textureID;
	blocks[id].textureID[4] = textureID;
	blocks[id].textureID[5] = textureID;
	blocks[id].toString = strdup(name);
	va_start(args, count);
	for (i = 0 ; i < count ; i++)
	{
		faceID = va_arg(args, unsigned);
		textureID = va_arg(args, unsigned);
		blocks[id].textureID[faceID] = textureID;
	}
	va_end(args);
}

/** load every blocks */
static void	createAllBlocks(t_block *blocks)
{
	blockCreate(blocks, BLOCK_AIR, TEXTURE_BLOCK_NONE, "air", 0);
	blockCreate(blocks, BLOCK_DIRT, TEXTURE_BLOCK_DIRT, "dirt", 0);
	blockCreate(blocks, BLOCK_GRASS, TEXTURE_BLOCK_GRASS_SIDE, "grass", 2, BLOCK_FACE_BOT, TEXTURE_BLOCK_DIRT, BLOCK_FACE_TOP, TEXTURE_BLOCK_GRASS_TOP);
	blockCreate(blocks, BLOCK_STONE, TEXTURE_BLOCK_STONE, "stone", 0);
	blockCreate(blocks, BLOCK_SAND, TEXTURE_BLOCK_SAND, "sand", 0);
	blockCreate(blocks, BLOCK_BEDROCK, TEXTURE_BLOCK_BEDROCK, "bedrock", 0);
	blockCreate(blocks, BLOCK_ICE, TEXTURE_BLOCK_ICE, "ice", 0);
	blockCreate(blocks, BLOCK_PACKED_ICE, TEXTURE_BLOCK_PACKED_ICE, "ice_packed", 0);
}

void		loadBlocks(t_renderer *renderer)
{
	createAllBlocks(renderer->blocks);
	createBlockTextures(renderer);
}


t_block		*getBlockByID(unsigned id)
{
	return (g_game->renderer.blocks + id);
}

int			isBlockVisible(unsigned id)
{
	return (id != BLOCK_AIR);
}
