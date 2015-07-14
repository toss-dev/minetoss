/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_terrain.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 17:26:27 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/12 23:11:13 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

static void loadTerrainInstanceUniforms(t_renderer *renderer, t_terrain *terrain)
{
	static float	m[16];

	matrix_identity(m);
	matrix_translate(m, new_vec3(terrain->index.x * TERRAIN_SIZEX, terrain->index.y * TERRAIN_SIZEY, terrain->index.z * TERRAIN_SIZEZ));
	loadUniformMatrix(renderer->programs[PROGRAM_TERRAIN].transf_matrix, m);
}


static void bindTerrainTexture(t_renderer *renderer, double dist)
{
	unsigned	id;

	if (dist <= 2)
	{
		id = RESOLUTION_BLOCK_ATLAS_16;
	}
	else if (dist <= 6)
	{
		id = RESOLUTION_BLOCK_ATLAS_8;
	}
	else if (dist <= 8)
	{
		id = RESOLUTION_BLOCK_ATLAS_4;
	}
	else
	{
		id = RESOLUTION_BLOCK_ATLAS_2;
	}
	glBindTexture(GL_TEXTURE_2D, renderer->block_atlas[id]);
}

static void renderTerrain(t_renderer *renderer, t_terrain *terrain)
{
	t_vec3		mesh_pos;
	unsigned	i;
	double		dist;

	if (!terrainHasState(terrain, TERRAIN_LOADED))
	{
		return ;
	}

	loadTerrainInstanceUniforms(renderer, terrain);

	for (i = 0 ; i < MESH_PER_TERRAIN ; i++)
	{
		if (terrain->meshes[i].vertex_count == 0)
		{
			continue ;
		}

		dist = point3_dist(terrain->index, getTerrainIndexForPos(renderer->camera.pos));

		if (dist > TERRAIN_RENDER_DISTANCE)
		{
			continue ;
		}
		
		mesh_pos = new_vec3(terrain->index.x * TERRAIN_SIZEX + TERRAIN_SIZEX / 2,	//center of the mesh
							i * MESH_SIZEY + MESH_SIZEY / 2 + terrain->index.y * TERRAIN_SIZEY,
							terrain->index.z * TERRAIN_SIZEZ + TERRAIN_SIZEZ / 2);

		if (dist <= 1 || isInCameraFrustum(&(renderer->camera), mesh_pos, 30))
		{
			bindTerrainTexture(renderer, dist);	//bind texture depending on distance (bitmapping)
			renderModel(terrain->meshes + i);
		}

	}
}

static void loadTerrainUniforms(t_world *world, t_renderer *renderer, t_program *program)
{
	loadUniformMatrix(program->view_matrix, renderer->camera.view_matrix);
	loadUniformVec(program->fog_color, world->weather.fog_color);
	loadUniformFloat(program->fog_density, world->weather.fog_density);
	loadUniformFloat(program->fog_gradient, world->weather.fog_gradient);
	loadUniformVec(program->sun_color, world->weather.sun_color);
	loadUniformVec(program->sun_position, world->weather.sun_pos);
}

void 		renderTerrains(t_world *world, t_renderer *renderer)
{
	t_program	*program;

	program = renderer->programs + PROGRAM_TERRAIN;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glActiveTexture(GL_TEXTURE0);

	glhUseProgram(program);
	{
		loadTerrainUniforms(world, renderer, program);

		HTAB_ITER_START(world->terrains, t_terrain, terrain)
		{
			renderTerrain(renderer, terrain);
		}
		HTAB_ITER_END(world->terrain, t_terrain, terrain)
	}
	glhStopUseProgram();

	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}
