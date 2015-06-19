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

#include "main.h"

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

static void	textureCreate(t_texture *textures, unsigned id, char const *name)
{
	char	buffer[256];

	sprintf(buffer, "./assets/textures/blocks/%s.png", name);
	if (loadPngFile(buffer, textures + id) == -1)
	{
		textures[id].pixels = NULL;
	}
}

/** load every block textures */
static void	createAllTextures(t_texture *textures)
{
	textureCreate(textures, TEXTURE_BLOCK_NONE, "none");
	textureCreate(textures, TEXTURE_BLOCK_DIRT, "dirt");
	textureCreate(textures, TEXTURE_BLOCK_GRASS_SIDE, "grass_side");
	textureCreate(textures, TEXTURE_BLOCK_GRASS_TOP, "grass_top");
	textureCreate(textures, TEXTURE_BLOCK_BEDROCK, "bedrock");
	textureCreate(textures, TEXTURE_BLOCK_STONE, "stone");
	textureCreate(textures, TEXTURE_BLOCK_SAND, "sand");
	textureCreate(textures, TEXTURE_BLOCK_ICE, "ice");
	textureCreate(textures, TEXTURE_BLOCK_PACKED_ICE, "ice_packed");
}

static unsigned getPixelAt(unsigned char *pixels, unsigned x, unsigned y, unsigned width, unsigned index)
{
	return (pixels[y * width * 4 + x * 4 + index]);
}

/** id is r, g, b or a */
static unsigned char getPixelsAverage(unsigned char *pixels, unsigned x, unsigned y, unsigned width, float ratio, unsigned id)
{
	unsigned tmp;

	tmp = getPixelAt(pixels, x / ratio, y / ratio, width, id)
			+ getPixelAt(pixels, x / ratio + 1, y / ratio, width, id)
			+ getPixelAt(pixels, x / ratio + 1, y / ratio + 1, width, id)
			+ getPixelAt(pixels, x / ratio, y / ratio + 1, width, id);
	return (tmp / 4);
}

static unsigned char *resizeTexture(unsigned char *pixels, unsigned width, unsigned height, float ratio)
{
	unsigned char	*reduced;
	unsigned 		x;
	unsigned 		y;
	unsigned 		index;
	unsigned 		w;
	unsigned 		h;

	if (ratio == 1)
	{
		return (ft_memdup(pixels, width * height * 4));
	}
	w = width * ratio;
	h = height * ratio;
	if ((reduced = (unsigned char*)malloc(sizeof(unsigned char) * w * h * 4)) == NULL)
		return (NULL);
	index = 0;
	for (x = 0 ; x < w ; x++)
	{
		for (y = 0 ; y < h ; y++)
		{
			index = y * w * 4 + x * 4;
			reduced[index + 0] = getPixelsAverage(pixels, x, y, width, ratio, 0);
			reduced[index + 1] = getPixelsAverage(pixels, x, y, width, ratio, 1);
			reduced[index + 2] = getPixelsAverage(pixels, x, y, width, ratio, 2);
			reduced[index + 3] = getPixelsAverage(pixels, x, y, width, ratio, 3);
		}
	}
	return (reduced);
}

static void	generateBlockAtlas(unsigned glID, unsigned char *pixels, unsigned width, unsigned height, float factor)
{
	char 			buffer[128];
	unsigned char 	*reduced;

	sprintf(buffer, "./assets/textures/blocks/texture_atlas_%dx%d.png", (int)(width * factor), (int)(height * factor));
	reduced = resizeTexture(pixels, width, height, factor);	//resize the texture
	lodepng_encode32_file(buffer, reduced, width * factor, height * factor);	//save the file

	//opengl stuff to create a texture
	glBindTexture(GL_TEXTURE_2D, glID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width * factor, height * factor, 0, GL_RGBA, GL_UNSIGNED_BYTE, reduced);
	free(reduced);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

static void	createTextureBlockAtlas(t_renderer *renderer, t_texture *textures)
{
	unsigned char	*pixels;
	unsigned 		i;

	pixels = (unsigned char*)malloc(sizeof(unsigned char) * BLOCK_TEXTURE_BYTES * TEXTURE_BLOCK_MAX);
	for (i = 0 ; i < TEXTURE_BLOCK_MAX ; i++)
	{
		if (textures[i].pixels)
		{
			memcpy(pixels + i * BLOCK_TEXTURE_BYTES, textures[i].pixels, BLOCK_TEXTURE_BYTES);
		}
		else
		{
			memset(pixels + i * BLOCK_TEXTURE_BYTES, 0xFF, BLOCK_TEXTURE_BYTES);
		}
		free(textures[i].pixels);
		textures[i].pixels = NULL;
	}
	glGenTextures(RESOLUTION_BLOCK_ATLAS_MAX, renderer->block_atlas);

	generateBlockAtlas(renderer->block_atlas[RESOLUTION_BLOCK_ATLAS_16], pixels, BLOCK_TEXTURE_WIDTH, BLOCK_TEXTURE_HEIGHT * TEXTURE_BLOCK_MAX, 1);
	generateBlockAtlas(renderer->block_atlas[RESOLUTION_BLOCK_ATLAS_8], pixels, BLOCK_TEXTURE_WIDTH, BLOCK_TEXTURE_HEIGHT * TEXTURE_BLOCK_MAX, 0.5f);
	generateBlockAtlas(renderer->block_atlas[RESOLUTION_BLOCK_ATLAS_4], pixels, BLOCK_TEXTURE_WIDTH, BLOCK_TEXTURE_HEIGHT * TEXTURE_BLOCK_MAX, 0.25f);
	generateBlockAtlas(renderer->block_atlas[RESOLUTION_BLOCK_ATLAS_2], pixels, BLOCK_TEXTURE_WIDTH, BLOCK_TEXTURE_HEIGHT * TEXTURE_BLOCK_MAX, 0.125f);
	free(pixels);
}

void		loadBlocks(t_renderer *renderer)
{
	t_texture	textures[TEXTURE_BLOCK_MAX];

	createAllBlocks(renderer->blocks);
	createAllTextures(textures);
	createTextureBlockAtlas(renderer, textures);
}

t_block		*getBlockByID(unsigned id)
{
	return (g_game->renderer.blocks + id);
}

int			isBlockVisible(unsigned id)
{
	return (id != BLOCK_AIR);
}
