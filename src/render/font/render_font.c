/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 16:33:11 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/07 18:50:23 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void loadUniformFontMatrix(t_program *program, t_font_model *model)
{
	float	matrix[16];

	matrix_identity(matrix);
	matrix_translate(matrix, model->pos);
	matrix_rotate(matrix, new_vec3(1, 0, 0), model->rot.x);
	matrix_rotate(matrix, new_vec3(0, 1, 0), model->rot.y);
	matrix_rotate(matrix, new_vec3(0, 0, 1), model->rot.z);
	matrix_scale(matrix, model->scale);

	loadUniformMatrix(program->transf_matrix, matrix);
}

static void	renderFontModel(t_program *program, t_font_model *model)
{
	glBindTexture(GL_TEXTURE_2D, model->textureID);

	loadUniformFontMatrix(program, model);
	loadUniformVec(program->font_color, model->color);

	glBindVertexArray(model->vaoID);

	glEnableVertexAttribArray(ATTR_POSITION);
	glEnableVertexAttribArray(ATTR_UV);

	glDrawArrays(GL_TRIANGLES, 0, model->vertex_count);

	glDisableVertexAttribArray(ATTR_POSITION);
	glDisableVertexAttribArray(ATTR_UV);

	glBindVertexArray(0);
}

void		renderFont(t_program *program, t_font_model *model)
{
	glActiveTexture(GL_TEXTURE0);
	glUseProgram(program->id);
	{
		renderFontModel(program, model);
	}
	glUseProgram(0);
}
