/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 18:11:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/15 15:34:55 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

static void	updateCameraVectors(t_camera *camera)
{
	if (camera->state & C_MOVE_FORWARD)
	{
		camera->vec_pos.x = camera->look_vec.x;
		camera->vec_pos.y = camera->look_vec.y;
		camera->vec_pos.z = camera->look_vec.z;
	}
	else if (camera->state & C_MOVE_BACKWARD)
	{
		camera->vec_pos.x = -camera->look_vec.x;
		camera->vec_pos.y = -camera->look_vec.y;
		camera->vec_pos.z = -camera->look_vec.z;
	}
	else if (camera->state & C_MOVE_LEFT)
	{
		camera->vec_pos = new_vec3(camera->look_vec.z, 0, -camera->look_vec.x);
	}
	else if (camera->state & C_MOVE_RIGHT)
	{
		camera->vec_pos = new_vec3(-camera->look_vec.z, 0, camera->look_vec.x);
	}
	else
	{
		camera->vec_pos.x = 0;
		camera->vec_pos.y = 0;
		camera->vec_pos.z = 0;
	}
}

static void	moveCamera(t_camera *camera)
{
	static float	rot_speed = 0.02f;
	static float	speed = 1.0f;

	camera->pitch += camera->vec_rot.x * rot_speed;
	camera->yaw += camera->vec_rot.y * rot_speed;
	camera->pos.x += camera->vec_pos.x * speed;
	camera->pos.y += camera->vec_pos.y * speed;
	camera->pos.z += camera->vec_pos.z * speed;
}

void		updateCamera(t_camera *camera)
{
	camera->look_vec = vec3_normalize(vec3_pitch_yaw(camera->pitch, camera->yaw));
	updateCameraVectors(camera);
	moveCamera(camera);
	matrix_view(camera->view_matrix, camera->pitch, camera->yaw, camera->roll, camera->pos);
}

/** my frustrum culling, check if not too far and if in field of view */
/*


             \-------------/		
              \  p        /
               \         /
                \       /	        p: point to test
                 \     /
                  \   /             imprecision: make field of view larger
                   \ /
                  / e \				e: eye
                  \___/				

*/
int			isInCameraFrustum(t_camera *camera, t_vec3 point, float impresicion)
{
	t_vec3	to_chunk_vector;
	double 	dot;
	double	angle;

	to_chunk_vector = vec3_normalize(vec3_sub(point, camera->pos));
	dot = vec3_dot_product(to_chunk_vector, camera->look_vec);
	angle = TO_DEGREE(acos(dot));
	return (angle < camera->fov / 2 + impresicion);
}

static void	bind_projection_matrix(t_camera camera, t_program *program)
{
	float	*matrix;
	float	aspect;

	aspect = WIDTH / (float)HEIGHT;
	matrix = matrix_projection(camera.fov, camera.near_dist, camera.far_dist, aspect);
	if (matrix == NULL)
	{
		logger_log(LOG_ERROR, "Not enough memory (projection matrix)");
	}
	glUseProgram(program->id);
	logger_log(LOG_FINE, "Binding projection matrix to program: %d", program->id);
	glhLoadUniformMatrix(program, U_PROJ_MATRIX, matrix);
	glUseProgram(0);
	free(matrix);
}

void		loadCamera(t_renderer *renderer)
{
	int	i;

	logger_log(LOG_FINE, "Setting camera's data");
	renderer->camera.pos = new_vec3(0, TERRAIN_SIZEY, 0);
	renderer->camera.vec_rot = new_vec3(0, 0, 0);
	renderer->camera.vec_pos = new_vec3(0, 0, 0);
	renderer->camera.fov = 70;
	renderer->camera.near_dist = 0.1f;
	renderer->camera.far_dist = 2000;
	for (i = 0; i < PROGRAM_MAX; i++)
	{
		bind_projection_matrix(renderer->camera, renderer->programs + i);
	}
	renderer->camera.state = 0;
	renderer->camera.pitch = 0;
	renderer->camera.yaw = M_PI / 2;
	renderer->camera.roll = 0;
	renderer->camera.look_vec = new_vec3(1, 0, 0);
	if ((renderer->camera.view_matrix = new_matrix()) == NULL)
	{
		logger_log(LOG_ERROR, "Not enough memory");
	}
}
