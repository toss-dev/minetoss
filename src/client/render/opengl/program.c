/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 12:55:12 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/13 14:19:36 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

void		programDelete(t_program *program)
{
	shaderDelete(program->id, program->vertex_shader);
	shaderDelete(program->id, program->fragment_shader);
	glDeleteProgram(program->id);
}

static void	bindAttributes(int program_id)
{
	glBindAttribLocation(program_id, ATTR_POSITION, "position");
	glBindAttribLocation(program_id, ATTR_NORMAL, "normal");
	glBindAttribLocation(program_id, ATTR_UV, "uv");
}

static void	bindUniforms(t_program *program)
{
	logger_log(LOG_FINE, "Creating uniform variables");
	
	program->uniforms[U_TRANSF_MATRIX] = glGetUniformLocation(program->id, "transf_matrix");
	program->uniforms[U_VIEW_MATRIX] = glGetUniformLocation(program->id, "view_matrix");
	program->uniforms[U_PROJ_MATRIX] = glGetUniformLocation(program->id, "proj_matrix");
	
	program->uniforms[U_FOG_COLOR] = glGetUniformLocation(program->id, "fog_color");
	program->uniforms[U_FOG_DENSITY] = glGetUniformLocation(program->id, "fog_density");
	program->uniforms[U_FOG_GRADIENT] = glGetUniformLocation(program->id, "fog_gradient");
	
	program->uniforms[U_SUN_COLOR] = glGetUniformLocation(program->id, "sun_color");
	program->uniforms[U_SUN_POSITION] = glGetUniformLocation(program->id, "sun_position");

	program->uniforms[U_DAY_FACTOR] = glGetUniformLocation(program->id, "day_factor");
	program->uniforms[U_DAY_RATIO] = glGetUniformLocation(program->id, "day_ratio");

	program->uniforms[U_CUBEMAP_DAY] = glGetUniformLocation(program->id, "cubemap_day");
	program->uniforms[U_CUBEMAP_NIGHT] = glGetUniformLocation(program->id, "cubemap_night");
	
	program->uniforms[U_FONT_COLOR] = glGetUniformLocation(program->id, "font_color");
	
	program->uniforms[U_USE_ANIMATION] = glGetUniformLocation(program->id, "use_animation");
	program->uniforms[U_ANIM_TRANSF_MATRIX] = glGetUniformLocation(program->id, "anim_transf_matrix");
}

static void	loadProgram(t_program *program, char const *vertex, char const *fragment)
{
	char		buffer[64];

	program->id = glCreateProgram();
	sprintf(buffer, "./assets/shaders/%s", vertex);
	program->vertex_shader = loadShader(buffer, GL_VERTEX_SHADER);
	sprintf(buffer, "./assets/shaders/%s", fragment);
	program->fragment_shader = loadShader(buffer, GL_FRAGMENT_SHADER);
	glAttachShader(program->id, program->vertex_shader);
	glAttachShader(program->id, program->fragment_shader);
	bindAttributes(program->id);
	glLinkProgram(program->id);
	glValidateProgram(program->id);
	bindUniforms(program);
}

void			loadPrograms(t_renderer *renderer)
{
	t_program	*program;

	program = renderer->programs;

	loadProgram(program + PROGRAM_TERRAIN, "terrain.vertex", "terrain.fragment");
	loadProgram(program + PROGRAM_SKYBOX, "skybox.vertex", "skybox.fragment");
	loadProgram(program + PROGRAM_FONT, "font.vertex", "font.fragment");
	loadProgram(program + PROGRAM_QUAD, "quad.vertex", "quad.fragment");
	loadProgram(program + PROGRAM_VOXEL_MODEL, "voxel_model.vertex", "voxel_model.fragment");
}
