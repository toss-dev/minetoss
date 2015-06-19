/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 00:05:11 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/03 00:06:01 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCKS_H
# define BLOCKS_H

# include "opengl.h"

/*
**	REMINDER:
**
**	- HOW TO ADD A BLOCK:
**		add it to block enum before BLOCK_MAX
**
**	- HOW TO ADD A BLOCK TEXTURE SET:
**		add it textures enum e_block_texture_id before TEXTURE_BLOCK_MAX
**		load textures into block.c
*/

# define BLOCK_TEXTURE_WIDTH 16
# define BLOCK_TEXTURE_HEIGHT BLOCK_TEXTURE_WIDTH
# define BLOCK_TEXTURE_BYTES (BLOCK_TEXTURE_WIDTH * BLOCK_TEXTURE_HEIGHT * 4)
# define TEXTURE_UV_WIDTH_UNIT 1
# define TEXTURE_UV_HEIGHT_UNIT (1 / (float)TEXTURE_BLOCK_MAX)

enum	e_blocks_id
{
	BLOCK_AIR,
	BLOCK_DIRT,
	BLOCK_STONE,
	BLOCK_GRASS,
	BLOCK_SAND,
	BLOCK_BEDROCK,
	BLOCK_ICE,
	BLOCK_PACKED_ICE,
	BLOCK_MAX
};

enum e_cube_face
{
	BLOCK_FACE_LEFT,
	BLOCK_FACE_RIGHT,
	BLOCK_FACE_TOP,
	BLOCK_FACE_BOT,
	BLOCK_FACE_FRONT,
	BLOCK_FACE_BACK
};

enum e_block_texture_id
{
	TEXTURE_BLOCK_NONE,
	TEXTURE_BLOCK_DIRT,
	TEXTURE_BLOCK_GRASS_SIDE,
	TEXTURE_BLOCK_GRASS_TOP,
	TEXTURE_BLOCK_STONE,
	TEXTURE_BLOCK_SAND,
	TEXTURE_BLOCK_BEDROCK,
	TEXTURE_BLOCK_ICE,
	TEXTURE_BLOCK_PACKED_ICE,
	TEXTURE_BLOCK_MAX
};

typedef struct 	s_block
{
	unsigned	id;
	char		*toString;
	unsigned	textureID[6];	//texture id for each face
}				t_block;

void 			cleanBlocks(t_block *blocks);
int				isBlockVisible(unsigned id);

#endif
