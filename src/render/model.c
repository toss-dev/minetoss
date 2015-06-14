/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/13 04:23:44 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 04:24:23 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opengl.h"

t_model	new_model(GLenum glmode)
{
	t_model	model;

	model.vaoID = 0;
	model.vboID = 0;
	model.vertex_count = 0;
	model.glmode = glmode;
	return (model);
}
/**
**		t_vertex	buffer[] = {
**			{{-1, 1, 0}, {0, 1, 0}, {0, 0}},
**			{{-1, -1, 0}, {0, 1, 0}, {0, 1}},
**			{{1, -1, 0}, {0, 1, 0}, {1, 1}},
**			{{-1, 1, 0}, {0, 1, 0}, {0, 0}},
**			{{1, -1, 0}, {0, 1, 0}, {1, 1}},
**			{{1, 1, 0}, {0, 1, 0}, {1, 0}}
**		};
**
**	return false if initialization failed
**
*/
bool	initModel(t_model *model, t_vertex *vertices, unsigned vertex_count)
{
	model->vaoID = glhGenVAO();
	model->vboID = glhGenVBO();
	
	glBindVertexArray(model->vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, model->vboID);

	glhVBOData(GL_ARRAY_BUFFER, vertices, vertex_count * sizeof(t_vertex), model->glmode);

	glhVertexAttribPointer(ATTR_POSITION, 	3, 3 + 3 + 2, 0);
	glhVertexAttribPointer(ATTR_NORMAL, 	3, 3 + 3 + 2, 3);
	glhVertexAttribPointer(ATTR_UV, 		2, 3 + 3 + 2, 3 + 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	model->vertex_count = vertex_count;

	return (true);
}

bool	updateModelVBO(t_model *model, t_vertex *vertices, unsigned vertex_count)
{
	glBindBuffer(GL_ARRAY_BUFFER, model->vboID);
	glhVBOClear(GL_ARRAY_BUFFER, model->vertex_count * sizeof(t_vertex), model->glmode);
	model->vertex_count = vertex_count;
	glhVBOData(GL_ARRAY_BUFFER, vertices, model->vertex_count * sizeof(t_vertex), model->glmode);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return (true);
}

void 	renderModel(t_model *model)
{
	glBindVertexArray(model->vaoID);

	glEnableVertexAttribArray(ATTR_POSITION);
	glEnableVertexAttribArray(ATTR_NORMAL);
	glEnableVertexAttribArray(ATTR_UV);

	glDrawArrays(GL_TRIANGLES, 0, model->vertex_count);

	glEnableVertexAttribArray(ATTR_POSITION);
	glEnableVertexAttribArray(ATTR_NORMAL);
	glEnableVertexAttribArray(ATTR_UV);
	glBindVertexArray(0);
}

void 	modelDelete(t_model *model)
{
	glhDeleteVAO(&(model->vaoID));
	glhDeleteVBO(&(model->vboID), model->vertex_count * sizeof(t_vertex));
	model->vertex_count = 0;
}