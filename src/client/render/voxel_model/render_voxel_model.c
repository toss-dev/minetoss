/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxel_model.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

void	initVoxelRenderer(t_renderer *renderer)
{
	renderer->voxels[VOXEL_BLUE] = new_vec3(0, 0, 1);
	renderer->voxels[VOXEL_RED] = new_vec3(1, 0, 0);
	renderer->voxels[VOXEL_GREEN] = new_vec3(0, 1, 0);
	renderer->voxels[VOXEL_YELLOW] = new_vec3(1, 0, 1);
}

static void	loadVoxelModelUniforms(t_program *program, t_entity *entity)
{
	float	transf_matrix[16];

	matrix_identity(transf_matrix);
	matrix_translate(transf_matrix, entity->pos);
/*	matrix_rotate(transf_matrix, new_vec3(1, 0, 0), entity->rot.x);
	matrix_rotate(transf_matrix, new_vec3(0, 1, 0), entity->rot.y);
	matrix_rotate(transf_matrix, new_vec3(0, 0, 1), entity->rot.z);
	matrix_scale(transf_matrix, entity->scale);
*/
	glhLoadUniformMatrix(program, U_TRANSF_MATRIX, transf_matrix);
}

static void	loadAnimationUniforms(t_program *program, t_animation *animation, unsigned int frameID)
{
	float	anim_transf_matrix[16];

	frameID = frameID % animation->frame_count;
	matrix_translate(anim_transf_matrix, animation->frames[frameID].pos);
	matrix_rotate(anim_transf_matrix, new_vec3(1, 0, 0), animation->frames[frameID].rot.x);
	matrix_rotate(anim_transf_matrix, new_vec3(0, 1, 0), animation->frames[frameID].rot.y);
	matrix_rotate(anim_transf_matrix, new_vec3(0, 0, 1), animation->frames[frameID].rot.z);
	matrix_scale(anim_transf_matrix, animation->frames[frameID].scale);
	glhLoadUniformMatrix(program, U_ANIM_TRANSF_MATRIX, anim_transf_matrix);
}

/**
**	render the given t_voxel_part at the given position
**
**	animation: 	the animation to use for this voxel part
**	frameID: 	frameID for this animation to use
*/
static void	renderVoxelModelPart(t_program *program, t_voxel_part *part, t_animation *animation, unsigned int frameID)
{
	if (animation)
	{
		loadAnimationUniforms(program, animation, frameID);
		glhLoadUniformInt(program, U_USE_ANIMATION, 1);
	}
	else
	{
		glhLoadUniformInt(program, U_USE_ANIMATION, 0);
	}
	(void)part;
	(void)animation;
	(void)frameID;
}

void	renderVoxelModel(t_renderer *renderer, t_entity *entity)
{
	t_program		*program;
	t_voxel_model	*model;
	unsigned int 	i;

	if (entity->modelID >= VOXEL_MODEL_MAX)
	{
		logger_log(LOG_ERROR, "Tried to render an unknown model while rendering an entity!");
		return ;
	}
	program = renderer->programs + PROGRAM_VOXEL_MODEL;
	model = renderer->voxel_models + entity->modelID;
	glhUseProgram(program);
	{
		loadVoxelModelUniforms(program, entity);
		for (i = 0 ; i < model->parts_count ; i++)
		{
			//here animation uniform should be loaded
			renderVoxelModelPart(program, model->parts + i, NULL, 0);
		}
	}
}
