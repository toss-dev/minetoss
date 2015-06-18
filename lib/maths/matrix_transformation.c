/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 12:07:07 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/10 14:33:16 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

static void	get_rotate_floats(float f[16], t_vec3 axis, float angle)
{
	float	c;
	float	s;
	float	cm;
	float	xyz[6];

	c = cos(angle);
	s = sin(angle);
	cm = 1.0f - c;
	xyz[0] = axis.x * axis.y;
	xyz[1] = axis.y * axis.z;
	xyz[2] = axis.x * axis.z;
	xyz[3] = axis.x * s;
	xyz[4] = axis.y * s;
	xyz[5] = axis.z * s;
	f[0] = axis.x * axis.x * cm + c;
	f[4] = xyz[0] * cm + xyz[5];
	f[8] = xyz[2] * cm - xyz[4];
	f[1] = xyz[0] * cm - xyz[5];
	f[5] = axis.y * axis.y * cm + c;
	f[9] = xyz[1] * cm + xyz[3];
	f[2] = xyz[2] * cm + xyz[4];
	f[6] = xyz[1] * cm - xyz[3];
	f[10] = axis.z * axis.z * cm + c;
}

void		matrix_rotate(float *m, t_vec3 axis, float angle)
{
	float	f[16];
	float	tmp[16];

	axis = vec3_normalize(axis);
	get_rotate_floats(f, axis, angle);
	tmp[0] = m[0] * f[0] + m[1] * f[4] + m[2] * f[8];
	tmp[4] = m[4] * f[0] + m[5] * f[4] + m[6] * f[8];
	tmp[8] = m[8] * f[0] + m[9] * f[4] + m[10] * f[8];
	tmp[12] = m[12] * f[0] + m[13] * f[4] + m[14] * f[8];
	tmp[1] = m[0] * f[1] + m[1] * f[5] + m[2] * f[9];
	tmp[5] = m[4] * f[1] + m[5] * f[5] + m[6] * f[9];
	tmp[9] = m[8] * f[1] + m[9] * f[5] + m[10] * f[9];
	tmp[13] = m[12] * f[1] + m[13] * f[5] + m[14] * f[9];
	m[2] = m[0] * f[2] + m[1] * f[6] + m[2] * f[10];
	m[6] = m[4] * f[2] + m[5] * f[6] + m[6] * f[10];
	m[10] = m[8] * f[2] + m[9] * f[6] + m[10] * f[10];
	m[14] = m[12] * f[2] + m[13] * f[6] + m[12] * f[10];
	m[0] = tmp[0];
	m[4] = tmp[4];
	m[8] = tmp[8];
	m[12] = tmp[12];
	m[1] = tmp[1];
	m[5] = tmp[5];
	m[9] = tmp[9];
	m[13] = tmp[13];
}

void		matrix_scale(float *m, t_vec3 scale)
{
	m[0] = m[0] * scale.x;
	m[4] = m[4] * scale.x;
	m[8] = m[8] * scale.x;
	m[12] = m[12] * scale.x;
	m[1] = m[1] * scale.y;
	m[5] = m[5] * scale.y;
	m[9] = m[9] * scale.y;
	m[13] = m[13] * scale.y;
	m[2] = m[2] * scale.z;
	m[6] = m[6] * scale.z;
	m[10] = m[10] * scale.z;
	m[14] = m[14] * scale.z;
}

void		matrix_translate(float *m, t_vec3 translate)
{
	m[3] += m[0] * translate.x + m[1] * translate.y + m[2] * translate.z;
	m[7] += m[4] * translate.x + m[5] * translate.y + m[6] * translate.z;
	m[11] += m[8] * translate.x + m[9] * translate.y + m[10] * translate.z;
	m[15] += m[12] * translate.x + m[12] * translate.y + m[13] * translate.z;
}
