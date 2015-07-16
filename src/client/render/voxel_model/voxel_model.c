/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxel_model.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"


/**
**	Voxels models files structure are
**	raw t_voxel_model / t_voxel_part / t_animation structure bytes
*/

static void	parseVoxelModelPart(t_voxel_part *part, int fd)
{
	//vertices
	read(fd, &(part->vertex_count), sizeof(part->vertex_count));
	if ((part->vertex = (t_voxel_vertex*)malloc(sizeof(t_voxel_vertex) * part->vertex_count)) == NULL)
	{
		part->vertex_count = 0;
	}
	read(fd, part->vertex, sizeof(t_voxel_vertex) * part->vertex_count);

	//animation
	read(fd, &(part->animation_count), sizeof(part->animation_count));
	if ((part->animations = (t_animation*)malloc(sizeof(t_animation) * part->animation_count)) == NULL)
	{
		part->animation_count = 0;
		return ;
	}

	unsigned int i;
	for (i = 0 ; i < part->animation_count ; i++)
	{
		read(fd, &(part->animations[i].frame_count), sizeof(&(part->animations[i].frame_count)));
	}
}

static void	parseVoxelModel(t_voxel_model *model, int fd)
{
	unsigned int	i;

	read(fd, &(model->parts_count), sizeof(model->parts_count));
	if ((model->parts = (t_voxel_part*)malloc(sizeof(t_voxel_part) * model->parts_count)) == NULL)
	{
		model->parts_count = 0;
		return ;
	}
	for (i = 0 ; i < model->parts_count ; i++)
	{
		parseVoxelModelPart(model->parts + i, fd);
	}
}

static int	loadVoxelModel(t_voxel_model *model, char const *file)
{
	char	filepath[128];
	int 	fd;

	sprintf(filepath, "./assets/models/%s", file);
	logger_log(LOG_FINE, "Loading voxel model: %s\n", filepath);
	if ((fd = open(filepath, O_RDONLY)) == -1)
	{
		logger_log(LOG_ERROR, "Couldnt open file for reading: %s", filepath);
		return (-1);
	}
	parseVoxelModel(model, fd);
	close(fd);
	return (0);
}

void	loadVoxelModels(t_renderer *renderer)
{
	return ;
	
	loadVoxelModel(renderer->voxel_models + VOXEL_MODEL_PIG, "pig.voxel");
}