/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 02:26:08 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/07 18:21:21 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void 	deleteMesh(t_mesh *mesh)
{
	if (meshHasState(mesh, MESH_MODEL_INITIALIZED))
	{
		modelDelete(&(mesh->model));
	}
	free(mesh->data);
	mesh->data = NULL;
	mesh->vertex_count = 0;
	mesh->state = 0;
}

t_mesh	new_mesh(void)
{
	t_mesh	mesh;

	mesh.model = new_model(GL_STREAM_DRAW);
	mesh.data = NULL;
	mesh.state = 0;
	mesh.vertex_count = 0;
	return (mesh);
}

void	meshSetState(t_mesh *mesh, unsigned state)
{
	mesh->state = mesh->state | state;
}

void	meshUnsetState(t_mesh *mesh, unsigned state)
{
	mesh->state = mesh->state & ~(state);
}

bool	meshHasState(t_mesh *mesh, unsigned state)
{
	return (mesh->state & state);
}

void	updateMesh(t_world *world, t_terrain *terrain, unsigned meshID)
{
	if (!meshHasState(terrain->meshes + meshID, MESH_DATA_UP_TO_DATE))
	{
		updateTerrainMeshData(world, terrain, meshID);
		meshSetState(terrain->meshes + meshID, MESH_DATA_UP_TO_DATE);
		meshUnsetState(terrain->meshes + meshID, MESH_MODEL_UP_TO_DATE);
	}
}