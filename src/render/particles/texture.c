/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 15:27:02 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 19:01:26 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	loadTexture(GLuint id, char const *texture_file)
{
	t_texture	texture;

	logger_log(LOG_FINE, "Loading texture file: %s", texture_file);
	if (loadPngFile(texture_file, &texture) == -1)
	{
		return ;
	}
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0,
					texture.internalformat,
					texture.width, texture.height,
					0, texture.format, GL_UNSIGNED_BYTE, texture.pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.5f);
	free(texture.pixels);
}

static void	loadTextureAtlases(t_texture_atlas *texture, char const *file, int cols, int lines)
{
	char	buffer[256];

	glGenTextures(1, &(texture->id));
	sprintf(buffer, "./assets/textures/particles/%s", file);
	loadTexture(texture->id, buffer);
	texture->cols = cols;
	texture->lines = lines;
}

void		loadParticleTextures(t_renderer *renderer)
{
	loadTextureAtlases(renderer->textures_atlases + T_ATLAS_RAINDROP, "raindrop.png", 3, 1);
	loadTextureAtlases(renderer->textures_atlases + T_ATLAS_FLAMEDROP, "flamedrop.png", 5, 2);
	loadTextureAtlases(renderer->textures_atlases + T_ATLAS_FLAME, "flame.png", 8, 4);
	loadTextureAtlases(renderer->textures_atlases + T_ATLAS_EXPLOSION, "explosion.png", 5, 5);
	loadTextureAtlases(renderer->textures_atlases + T_ATLAS_LEAVE, "leaves.png", 1, 1);
	loadTextureAtlases(renderer->textures_atlases + T_ATLAS_MAGIC, "magic.png", 2, 2);
}
