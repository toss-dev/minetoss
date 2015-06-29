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

static void	prepareParticleInstance(t_camera *camera, t_program *program, t_particle *particle)
{
	float	m[16];
	t_vec3	vec;
	t_vec2	angle;

	vec = vec3_normalize(vec3_sub(particle->pos, camera->pos));
	angle.x = (1 - vec.x) / 2.0f * M_PI;
	angle.y = 0;
	matrix_identity(m);
	matrix_translate(m, particle->pos);
	matrix_rotate(m, new_vec3(0, 1, 0), -M_PI / 2 + angle.x);
	matrix_rotate(m, new_vec3(1, 0, 0), angle.y);
	matrix_scale(m, particle->scale);
	loadUniformMatrix(program->transf_matrix, m);
	loadUniformVec(program->particle_color, particle->color);


	(void)vec;
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
	(void)camera;
	(void)particle;
	return (1);
}

static void	renderParticle(t_particle *particle, t_renderer *renderer)
{
	if (shouldParticleBeRendered(&(renderer->camera), particle))
	{
		prepareParticleInstance(&(renderer->camera), renderer->programs + PROGRAM_PARTICLE, particle);
		prepareParticleTexture(renderer, particle);
		renderModel(&(renderer->quad_model));
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
	(void)world;


	static int i = 0;
	for (i = 0 ; i < 1 ; i++)
	{
		t_particle p = new_particle(new_vec3(0, 64, 0),
							new_vec3(10, 10, 10),
							new_vec3(0.5f, 0, 0),
							ParticleMoving, T_ATLAS_EXPLOSION, 999999);
		addParticle(renderer, p);
	}

	//TESTS END

	t_program	*program;

	program = renderer->programs + PROGRAM_PARTICLE;

	updateParticles(renderer);
	array_list_sort(renderer->particles, sortParticles);

	glUseProgram(program->id);
	{
		glBindVertexArray(renderer->quad_model.vaoID);

		glEnableVertexAttribArray(ATTR_POSITION);
		glEnableVertexAttribArray(ATTR_UV);

		loadUniformMatrix(program->view_matrix, renderer->camera.view_matrix);


		array_list_iter(renderer->particles, (t_iter_array_function)renderParticle, renderer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(ATTR_POSITION);
		glDisableVertexAttribArray(ATTR_UV);

		glBindVertexArray(0);
	}
	glUseProgram(0);

}
