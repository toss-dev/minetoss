/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include "opengl.h"
# include "maths.h"

# define FONT_TEXTURE_WIDTH 512
# define FONT_TEXTURE_HEIGHT 512
# define FONT_CHAR_WIDTH 32
# define FONT_CHAR_HEIGHT 64
# define FONT_ASCII_OFFSET ' '
# define FONT_CHAR_PER_COL (FONT_TEXTURE_HEIGHT / FONT_CHAR_HEIGHT)
# define FONT_CHAR_PER_LINE (FONT_TEXTURE_WIDTH / FONT_CHAR_WIDTH)
# define FONT_UV_UNIT_WIDTH (FONT_CHAR_WIDTH / (float)FONT_TEXTURE_WIDTH)
# define FONT_UV_UNIT_HEIGHT (FONT_CHAR_HEIGHT / (float)FONT_TEXTURE_HEIGHT)

typedef struct 	s_font_model
{
	GLuint		vaoID;
	GLuint		vboID;
	GLuint		textureID;
	unsigned	vertex_count;
	t_vec3		pos;
	t_vec3		scale;
	t_vec3		rot;
	t_vec3		color;
	float 		step;
}				t_font_model;

typedef struct 	s_font_vertex
{
	t_vec3	pos;
	t_vec2	uv;
}				t_font_vertex;

t_font_model	generateFontModel(t_vec3 color, t_vec3 pos, float step);
void 			deleteFontModel(t_font_model *model);
void 			loadFont(void);
void 			unloadFont(void);
void			renderFont(t_program *program, t_font_model *model);

void 			setFontModelPosition(t_font_model *model, t_vec3 pos);
void 			setFontModelRotation(t_font_model *model, t_vec3 rot);
void 			setFontModelScaling(t_font_model *model, t_vec3 scale);
void 			setFontModelText(t_font_model *model, char const *text);

float 			getFontStringWidth(t_font_model *model, char const *str);

#endif
