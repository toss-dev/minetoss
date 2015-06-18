/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 16:10:32 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/10 14:23:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

void		matrix_view(float *matrix, float pitch, float yaw, float roll, t_vec3 pos)
{
	matrix_identity(matrix);
	matrix_rotate(matrix, new_vec3(1, 0, 0), pitch);
	matrix_rotate(matrix, new_vec3(0, 1, 0), yaw);
	matrix_rotate(matrix, new_vec3(0, 0, 1), roll);
	matrix_translate(matrix, new_vec3(-pos.x, -pos.y, -pos.z));
}

float		*matrix_projection(float fov, float near, float far, float aspect)
{
	float	*matrix;
	float	x_scale;
	float	y_scale;
	float	frustrum;

	if ((matrix = new_matrix()) == NULL)
		return (NULL);
	y_scale = (float)((1.0f / tan(TO_RADIAN(fov / 2.0f))) * aspect);
	x_scale = y_scale / aspect;
	frustrum = far - near;
	matrix[0] = x_scale;
	matrix[5] = y_scale;
	matrix[10] = -((far + near) / frustrum);
	matrix[11] = -((2 * near * far) / frustrum);
	matrix[14] = -1;
	matrix[15] = 0;
	return (matrix);
}

t_vec3	vec3_pitch_yaw(float pitch, float yaw)
{
	t_vec3	vec;
	float	pitchcos;

	pitchcos = cos(pitch);
	vec.x = pitchcos * sin(yaw);
	vec.y = -sin(pitch);
	vec.z = -pitchcos * cos(yaw);
	return (vec);
}
