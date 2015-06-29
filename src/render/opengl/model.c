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

#include "main.h"

t_model	new_model(GLenum glmode)
{
	t_model	model;

	model.vaoID = 0;
	model.vboID = 0;
	model.vertices = NULL;
	model.vertex_count = 0;
	model.glmode = glmode;
	model.state = 0;
	return (model);
}

void 	setModelVertices(t_model *model, t_vertex *vertices, unsigned vertex_count)
{
	if (model->vertices)
	{
		free(model->vertices);
	}
	model->vertices = vertices;
	model->vertex_count = vertex_count;
	modelUnsetState(model, MODEL_VBO_UP_TO_DATE);
}

/** update model vbos depending on it data pointer and it vertex vertex_count*/
int	updateModelVBO(t_model *model)
{
	if (modelHasState(model, MODEL_VBO_UP_TO_DATE))
	{
		logger_log(LOG_WARNING, "Trying to update an unchanged model! canceling operation");
		return (0);
	}

	if (!modelHasState(model, MODEL_INITIALIZED))
	{
		model->vaoID = glhGenVAO();
		model->vboID = glhGenVBO();
		
		glBindVertexArray(model->vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, model->vboID);

		glhVBOData(GL_ARRAY_BUFFER, model->vertices, model->vertex_count * sizeof(t_vertex), model->glmode);

		glhVertexAttribPointer(ATTR_POSITION, 	3, 3 + 3 + 2, 0);
		glhVertexAttribPointer(ATTR_NORMAL, 	3, 3 + 3 + 2, 3);
		glhVertexAttribPointer(ATTR_UV, 		2, 3 + 3 + 2, 3 + 3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		modelSetState(model, MODEL_INITIALIZED);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, model->vboID);
		glhVBOData(GL_ARRAY_BUFFER, NULL, 0, model->glmode);
		glhVBOData(GL_ARRAY_BUFFER, model->vertices, model->vertex_count * sizeof(t_vertex), model->glmode);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	modelSetState(model, MODEL_VBO_UP_TO_DATE);
	modelUnsetState(model, MODEL_CLEARED);

	free(model->vertices);
	model->vertices = NULL;

	return (1);
}

void 	modelSetState(t_model *model, unsigned state)
{
	model->state = model->state | state;
}

void 	modelUnsetState(t_model *model, unsigned state)
{
	model->state = model->state & ~(state);
}

int 	modelHasState(t_model *model, unsigned state)
{
	return (model->state & state);
}


int	clearModelVBO(t_model *model)
{
	if (!modelHasState(model, MODEL_INITIALIZED) || modelHasState(model, MODEL_CLEARED))
	{
		return (0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, model->vboID);
	glhVBOData(GL_ARRAY_BUFFER, NULL, 0, model->glmode);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	modelSetState(model, MODEL_CLEARED);
	modelUnsetState(model, MODEL_VBO_UP_TO_DATE);
	return (1);
}

void 	renderModel(t_model *model)
{
	if (!modelHasState(model, MODEL_VBO_UP_TO_DATE))
	{
		updateModelVBO(model);
	}

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
	clearModelVBO(model);
	if (modelHasState(model, MODEL_INITIALIZED))
	{
		glhDeleteVAO(&(model->vaoID));
		glhDeleteVBO(&(model->vboID));
	}

	if (model->vertices)
	{
		free(model->vertices);
		model->vertices = NULL;
	}
	model->vertex_count = 0;
	model->state = 0;
}
