/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sky.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 18:43:01 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/15 18:43:42 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

static void	loadViewMatrix(t_renderer *renderer, t_program *program)
{
	float 	m[16];

	memcpy(m, renderer->camera.view_matrix, sizeof(m));
	m[3] = 0, m[7] = 0, m[11] = 0; //make it independant from camera positionm will always be rendered in screen
	matrix_rotate(m, new_vec3(1.0f, 0.0f, 0.0f), renderer->sky.rot.x);
	matrix_rotate(m, new_vec3(0.0f, 1.0f, 0.0f), renderer->sky.rot.y);
	matrix_rotate(m, new_vec3(0.0f, 0.0f, 1.0f), renderer->sky.rot.z);
	loadUniformMatrix(program->view_matrix, m);
}

static void prepareSkyUniform(t_world *world, t_renderer *renderer, t_program *program)
{
	loadViewMatrix(renderer, program);
	loadUniformVec(program->fog_color, world->weather.fog_color);
	loadUniformFloat(program->day_factor, 1);
	loadUniformFloat(program->day_ratio, 0.5f);
	loadUniformVec(program->sun_position, vec3_sub(world->weather.sun_pos, renderer->camera.pos));
	loadUniformVec(program->sun_color, world->weather.sun_color);
}

static void	renderSkybox(t_world *world, t_renderer *renderer)
{
	t_program	*program;

	program = renderer->programs + PROGRAM_SKYBOX;
	glUseProgram(program->id);
	{
		prepareSkyUniform(world, renderer, program);
		glBindVertexArray(renderer->sky.vaoID);
		glEnableVertexAttribArray(ATTR_POSITION);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, renderer->sky.cubemaps[CUBEMAP_DAY]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, renderer->sky.cubemaps[CUBEMAP_NIGHT]);
		glDrawArrays(GL_TRIANGLES, 0, renderer->sky.vertex_count);
		glDisableVertexAttribArray(ATTR_POSITION);
		glBindVertexArray(0);
	}
	glUseProgram(0);

}

void		renderSky(t_world *world, t_renderer *renderer)
{
	glDepthMask(GL_FALSE);
	{
		renderSkybox(world, renderer);
	}
	glDepthMask(GL_TRUE);
}
