/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 18:11:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/15 15:34:55 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_array_list	g_char_buffer;
GLuint 			g_textureID;

void 	loadFont(void)
{
	g_char_buffer = array_list_new(512, sizeof(t_font_vertex) * 6);
	g_textureID = glhLoadTexture("./font/font_buxton.png");
}

void 	unloadFont(void)
{
	array_list_delete(&g_char_buffer);
	glDeleteTextures(1, &g_textureID);
}

/*
	0 	3

	1 	2
*/

static void 	addCharVertices(unsigned line, unsigned col, t_vec3 index)
{
	t_font_vertex	vertex[6];

	vertex[0].pos = new_vec3(index.x - 0.5f, index.y + 0.5f, index.z);
	vertex[0].uv = new_vec2(FONT_UV_UNIT_WIDTH * col, FONT_UV_UNIT_HEIGHT * line);

	vertex[1].pos = new_vec3(index.x - 0.5f, index.y - 0.5f, index.z);
	vertex[1].uv = new_vec2(FONT_UV_UNIT_WIDTH * col, FONT_UV_UNIT_HEIGHT * line + FONT_UV_UNIT_HEIGHT);

	vertex[2].pos = new_vec3(index.x + 0.5f, index.y - 0.5f, index.z);
	vertex[2].uv = new_vec2(FONT_UV_UNIT_WIDTH * col + FONT_UV_UNIT_WIDTH, FONT_UV_UNIT_HEIGHT * line + FONT_UV_UNIT_HEIGHT);

	vertex[3] = vertex[0];

	vertex[4] = vertex[2];

	vertex[5].pos = new_vec3(index.x + 0.5f, index.y + 0.5f, index.z);
	vertex[5].uv = new_vec2(FONT_UV_UNIT_WIDTH * col + FONT_UV_UNIT_WIDTH, FONT_UV_UNIT_HEIGHT * line);

	array_list_add(&g_char_buffer, vertex);
}

static void 	generateFontBuffer(char const *str, float step)
{
	unsigned	i;
	unsigned	charID;
	unsigned	line;
	unsigned	col;
	t_vec3		index;

	index = new_vec3(0, 0, 0);
	for (i = 0 ; str[i] ; i++)
	{
		if (str[i] == '\n')
		{
			index.y--;
			index.x = 0;
			continue ;
		}
		charID = str[i] - FONT_ASCII_OFFSET;
		line = charID / FONT_CHAR_PER_LINE;
		col = charID % FONT_CHAR_PER_LINE;
		addCharVertices(line, col, index);
		index.x++;
		index.x += step;
	}
	(void)step;
}

float	getFontStringWidth(t_font_model *model, char const *str)
{
	size_t	len;

	len = strlen(str);
	return (len * model->scale.x + (len - 1) * model->step);
}

void 	setFontModelRotation(t_font_model *model, t_vec3 rot)
{
	model->rot = rot;
}

void 	setFontModelScaling(t_font_model *model, t_vec3 scale)
{
	model->scale = scale;
}

void 	setFontModelPosition(t_font_model *model, t_vec3 pos)
{
	model->pos = pos;
}

t_font_model	generateFontModel(char const *str, t_vec3 color, t_vec3 pos, float step)
{
	t_font_model	model;
	void 			*data;
	size_t			size;

	model.color = color;
	model.textureID = g_textureID;
	model.pos = pos;
	model.rot = new_vec3(0, 0, 0);
	model.scale = new_vec3(0.04f, 0.1f, 0);
	model.step = step;
	model.vaoID = glhGenVAO();
	model.vboID = glhGenVBO();

	generateFontBuffer(str, step);
	model.vertex_count = g_char_buffer.size * 6;
	data = array_list_to_buffer(g_char_buffer, ARRAY_LIST_RDONLY);
	size = model.vertex_count * sizeof(t_font_vertex);

	glBindVertexArray(model.vaoID);
	{
		glBindBuffer(GL_ARRAY_BUFFER, model.vboID);

		glhVBOData(GL_ARRAY_BUFFER, data, size, GL_STATIC_DRAW);

		glhVertexAttribPointer(ATTR_POSITION, 	3, 3 + 2, 0);
		glhVertexAttribPointer(ATTR_UV, 		2, 3 + 2, 3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	array_list_clear(&g_char_buffer);

	return (model);
}

void 		deleteFontModel(t_font_model *model)
{
	glhDeleteVAO(&(model->vaoID));
	glhDeleteVBO(&(model->vboID));
}
