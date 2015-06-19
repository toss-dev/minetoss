/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_particles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 16:33:11 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/07 18:50:23 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	prepareParticleInstance(t_camera camera, t_program program, t_particle *particle)
{
	static float	m[16];

	matrix_identity(m);
	matrix_translate(m, particle->pos);
	matrix_rotate(m, new_vec3(1, 0, 0), camera.pitch);
	matrix_rotate(m, new_vec3(0, 1, 0), camera.yaw);
	matrix_rotate(m, new_vec3(0, 0, 1), camera.roll);
	matrix_scale(m, particle->scale);
	loadUniformMatrix(program.transf_matrix, m);
	loadUniformVec(program.particle_color, particle->color);
}

static void	prepareParticleTexture(t_renderer *renderer, t_particle *particle)
{
	t_program	*program;

	program = renderer->programs + PROGRAM_PARTICLE;
	loadUniformInt(program->texture_atlas_cols, renderer->textures_atlases[particle->texture_id].cols);
	loadUniformInt(program->texture_atlas_lines, renderer->textures_atlases[particle->texture_id].lines);
	loadUniformInt(program->particle_texture_atlas_id, particle->texture_atlas_id);
	glBindTexture(GL_TEXTURE_2D, renderer->textures_atlases[particle->texture_id].id);
}

static int	shouldParticleBeRendered(t_camera *camera, t_particle *particle)
{
	t_vec3	vec;
	double 	dot;

	vec = vec3_normalize(vec3_sub(camera->pos, particle->pos));
	dot = vec3_dot_product(vec, camera->look_vec);
	return (dot < 0);
}

static void	renderParticle(t_particle *particle, t_renderer *renderer)
{
	if (shouldParticleBeRendered(&(renderer->camera), particle))
	{
		prepareParticleInstance(renderer->camera, renderer->programs[PROGRAM_PARTICLE], particle);
		prepareParticleTexture(renderer, particle);
		glDrawArrays(GL_TRIANGLES, 0, renderer->quad_model.vertex_count);
	}
}

static int 	sortParticles(void const *a, void const *b)
{
	t_particle	*pa;
	t_particle	*pb;

	pa = (t_particle*)a;
	pb = (t_particle*)b;
	return (pa->camera_dist < pb->camera_dist ? 1 : -1);
}

void		renderParticles(t_world *world, t_renderer *renderer)
{
	return ; //buggued
	
	//TESTS
/*	int i;
	for (i = 0 ; i < 16 ; i++)
	{
		t_particle p = new_particle(new_vec3(0, 120, 0),
							new_vec3(0.5f, 0.5f, 0.5f),
							new_vec3(0, 0, 0),
							new_vec3(0.5f, 0, 0),
							ParticleMoving, T_ATLAS_EXPLOSION, 120);
		p.pos_vec.x = rand_float_in_range(-1, 1);
		p.pos_vec.y = rand_float_in_range(-1, 1);
		p.pos_vec.z = -2;
		p.pos_vec = vec_multiply(vec_normalize(p.pos_vec), 0.25f);
		addParticle(renderer, p);
	}
*/

	//TESTS END

	t_program	*program;

	program = renderer->programs + PROGRAM_PARTICLE;

	updateParticles(renderer);
	array_list_sort(renderer->particles, sortParticles);

	glUseProgram(program->id);

	glBindVertexArray(renderer->quad_model.vaoID);

	glEnableVertexAttribArray(ATTR_POSITION);
	glEnableVertexAttribArray(ATTR_UV);
	glEnableVertexAttribArray(ATTR_NORMAL);

	glActiveTexture(GL_TEXTURE0);

	loadUniformMatrix(program->view_matrix, renderer->camera.view_matrix);
	loadUniformVec(renderer->programs[PROGRAM_PARTICLE].fog_color, world->weather.fog_color);
	loadUniformFloat(renderer->programs[PROGRAM_PARTICLE].fog_density, world->weather.fog_density);
	loadUniformFloat(renderer->programs[PROGRAM_PARTICLE].fog_gradient, world->weather.fog_gradient);

	array_list_iter(renderer->particles, (t_iter_array_function)renderParticle, renderer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(ATTR_POSITION);
	glDisableVertexAttribArray(ATTR_UV);
	glDisableVertexAttribArray(ATTR_NORMAL);

	glBindVertexArray(0);

	glUseProgram(0);
}
