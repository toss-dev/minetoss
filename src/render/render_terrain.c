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

#include "main.h"

static void loadTerrainInstanceUniforms(t_renderer *renderer, t_terrain *terrain)
{
	static float	m[16];

	matrix_identity(m);
	matrix_translate(m, new_vec3(terrain->index.x * TERRAIN_SIZEX, terrain->index.y * TERRAIN_SIZEY, terrain->index.z * TERRAIN_SIZEZ));
	matrix_rotate(m, new_vec3(1, 0, 0), 0);
	matrix_rotate(m, new_vec3(0, 1, 0), 0);
	matrix_rotate(m, new_vec3(0, 0, 1), 0);
	matrix_scale(m, new_vec3(1, 1, 1));
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

static void renderMesh(t_mesh *mesh)
{
	if (!meshHasState(mesh, MESH_MODEL_INITIALIZED))
	{
		initModel(&(mesh->model), mesh->data, mesh->vertex_count);
		meshSetState(mesh, MESH_MODEL_INITIALIZED);
		meshSetState(mesh, MESH_MODEL_UP_TO_DATE);
	}

	if (!meshHasState(mesh, MESH_MODEL_UP_TO_DATE))
	{
		updateModelVBO(&(mesh->model), mesh->data, mesh->vertex_count);
		meshSetState(mesh, MESH_MODEL_UP_TO_DATE);
	}
	renderModel(&(mesh->model));
}

static void	meshUnload(t_mesh *mesh)
{
	modelDelete(&(mesh->model));
	meshUnsetState(mesh, MESH_MODEL_INITIALIZED);
	meshUnsetState(mesh, MESH_MODEL_UP_TO_DATE);
}

static void renderTerrain(t_terrain *terrain, t_world_renderer *wr)
{
	double		dist;
	t_vec3		mesh_pos;
	unsigned	i;

	if (!terrainHasState(terrain, TERRAIN_LOADED))
	{
		return ;
	}
	loadTerrainInstanceUniforms(wr->renderer, terrain);
	for (i = 0 ; i < MESH_PER_TERRAIN ; i++)
	{
		if (terrain->meshes[i].vertex_count == 0)
		{
			continue ;
		}

		dist = point3_dist(terrain->index, getTerrainIndexForPos(wr->renderer->camera.pos));
		mesh_pos = new_vec3(terrain->index.x * TERRAIN_SIZEX + TERRAIN_SIZEX / 2,	//center of the mesh
							i * MESH_SIZEY + MESH_SIZEY / 2 + terrain->index.y * TERRAIN_SIZEY,
							terrain->index.z * TERRAIN_SIZEZ + TERRAIN_SIZEZ / 2);

		if (dist > CHUNK_RENDER_DISTANCE)
		{
			if (meshHasState(terrain->meshes + i, MESH_MODEL_INITIALIZED))
			{
				meshUnload(terrain->meshes + i);
			}
			continue ;
		}
		
		if (dist <= 1 || isInCameraFrustum(&(wr->renderer->camera), mesh_pos, 40))
		{
			bindTerrainTexture(wr->renderer, dist);	//bind texture depending on distance (bitmapping)
			renderMesh(terrain->meshes + i);
		}
	}
}

static void loadTerrainUniforms(t_world_renderer *wr)
{
	loadUniformMatrix(wr->program->view_matrix, wr->renderer->camera.view_matrix);
	loadUniformVec(wr->program->fog_color, wr->world->weather.fog_color);
	loadUniformFloat(wr->program->fog_density, wr->world->weather.fog_density);
	loadUniformFloat(wr->program->fog_gradient, wr->world->weather.fog_gradient);
	loadUniformVec(wr->program->sun_color, wr->world->weather.sun_color);
	loadUniformVec(wr->program->sun_position, wr->world->weather.sun_pos);
}

void 		renderTerrains(t_world *world, t_renderer *renderer)
{
	t_world_renderer	wr;

	wr.world = world;
	wr.renderer = renderer;
	wr.program = renderer->programs + PROGRAM_TERRAIN;

	glActiveTexture(GL_TEXTURE0);

	glhUseProgram(wr.program);
	{
		loadTerrainUniforms(&wr);
		htab_iter(world->terrains, (t_iter_function)renderTerrain, &wr);
	}
	glhStopUseProgram();
}
