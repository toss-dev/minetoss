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

#include "main.h"

void		programDelete(t_program *program)
{
	shaderDelete(program->id, program->vertex_shader);
	shaderDelete(program->id, program->fragment_shader);
	glDeleteProgram(program->id);
}

static void	bind_attributes(int program_id)
{
	glBindAttribLocation(program_id, ATTR_POSITION, "position");
	glBindAttribLocation(program_id, ATTR_NORMAL, "normal");
	glBindAttribLocation(program_id, ATTR_UV, "uv");
}

static void	bind_uniforms(t_program *program)
{
	logger_log(LOG_FINE, "Creating uniform variables");
	
	program->transf_matrix = glGetUniformLocation(program->id, "transf_matrix");
	program->view_matrix = glGetUniformLocation(program->id, "view_matrix");
	program->proj_matrix = glGetUniformLocation(program->id, "proj_matrix");
	
	program->fog_color = glGetUniformLocation(program->id, "fog_color");
	program->fog_density = glGetUniformLocation(program->id, "fog_density");
	program->fog_gradient = glGetUniformLocation(program->id, "fog_gradient");
	
	program->sun_color = glGetUniformLocation(program->id, "sun_color");
	program->sun_position = glGetUniformLocation(program->id, "sun_position");

	program->day_factor = glGetUniformLocation(program->id, "day_factor");
	program->day_ratio = glGetUniformLocation(program->id, "day_ratio");

	program->particle_color = glGetUniformLocation(program->id, "particle_color");
	program->texture_atlas_cols = glGetUniformLocation(program->id, "texture_atlas_cols");
	program->texture_atlas_lines = glGetUniformLocation(program->id, "texture_atlas_lines");
	program->particle_texture_atlas_id = glGetUniformLocation(program->id, "particle_texture_atlas_id");

	program->cubemap_day = glGetUniformLocation(program->id, "cubemap_day");
	program->cubemap_night = glGetUniformLocation(program->id, "cubemap_night");
	
	program->font_color = glGetUniformLocation(program->id, "font_color");
}

static t_program	load_program(char const *vertex, char const *fragment)
{
	t_program	program;
	char		buffer[64];

	program.id = glCreateProgram();
	sprintf(buffer, "./assets/shaders/%s", vertex);
	program.vertex_shader = loadShader(buffer, GL_VERTEX_SHADER);
	sprintf(buffer, "./assets/shaders/%s", fragment);
	program.fragment_shader = loadShader(buffer, GL_FRAGMENT_SHADER);
	glAttachShader(program.id, program.vertex_shader);
	glAttachShader(program.id, program.fragment_shader);
	bind_attributes(program.id);
	glLinkProgram(program.id);
	glValidateProgram(program.id);
	bind_uniforms(&program);
	return (program);
}

void			loadPrograms(t_renderer *renderer)
{
	renderer->programs[PROGRAM_TERRAIN] = load_program("cube.vertex", "cube.fragment");
	renderer->programs[PROGRAM_PARTICLE] = load_program("particle.vertex", "particle.fragment");
	renderer->programs[PROGRAM_SKYBOX] = load_program("skybox.vertex", "skybox.fragment");
	renderer->programs[PROGRAM_FONT] = load_program("font.vertex", "font.fragment");
}
