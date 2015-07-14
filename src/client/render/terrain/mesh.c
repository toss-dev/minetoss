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

#include "client/main.h"

/**
**	A mesh is a subvision of a terrain. (see terrain.c for what is a terrain)
**
**	It is the object that will be sent to openGL for rendering
**	The mesh contains every vertices of the chunk subdivision,
**	and openGL VAO's / VBO's
*/

/**
**	update terrain meshes
**
**	if the MODEL_VERTICES_UP_TO_DATE isnt set, the mesh is recalculated
**	and the model VBO has to be reset from the new mesh
*/
void	updateMeshes(t_world *world, t_terrain *terrain, unsigned meshID)
{
	if (!modelHasState(terrain->meshes + meshID, MODEL_VERTICES_UP_TO_DATE))
	{
		updateTerrainMeshData(world, terrain, meshID);
		modelSetState(terrain->meshes + meshID, MODEL_VERTICES_UP_TO_DATE);
		modelUnsetState(terrain->meshes + meshID, MODEL_VBO_UP_TO_DATE);
	}
}
