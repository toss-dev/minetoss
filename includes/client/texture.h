/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 15:24:31 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 19:01:36 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "opengl.h"

# define BMP_HEADER_SIZE 54

enum e_texture_id
{
	T_GUI_BUTTON_PRESSED,
	T_GUI_BUTTON_RELEASED,
	T_GUI_BUTTON_HOVERED,
	T_MAX
};

enum 	e_block_texture_atlas_resolution
{
	RESOLUTION_BLOCK_ATLAS_16,
	RESOLUTION_BLOCK_ATLAS_8,
	RESOLUTION_BLOCK_ATLAS_4,
	RESOLUTION_BLOCK_ATLAS_2,
	RESOLUTION_BLOCK_ATLAS_MAX
};

typedef struct	s_bmp
{
	GLubyte	*pixels;
	GLubyte	header[BMP_HEADER_SIZE];
	int		data_idx;
}				t_bmp;

typedef struct	s_texture
{
	unsigned	width;
	unsigned	height;
	GLubyte		*pixels;
	GLenum		internalformat;
	GLenum		format;
}				t_texture;

typedef struct 	s_texture_format
{
	char *extension;
	int (*decoder_funct)(char const *, t_texture *);
}				t_texture_format;

int				loadPngFile(char const *file, t_texture *texture);
int				loadBmpFile(char const *file, t_texture *texture);
void			bmpReverseYs(t_texture *texture);

#endif
