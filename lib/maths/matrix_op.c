/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 17:42:05 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/10 14:12:38 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

float	*matrix_combine(float *dst, float *s)
{
	static float	t[16];

	t[0] = dst[0] * s[0] + dst[4] * s[1] + dst[8] * s[2] + dst[12] * s[3];
	t[1] = dst[1] * s[0] + dst[5] * s[1] + dst[9] * s[2] + dst[13] * s[3];
	t[2] = dst[2] * s[0] + dst[6] * s[1] + dst[10] * s[2] + dst[14] * s[3];
	t[3] = dst[3] * s[0] + dst[7] * s[1] + dst[11] * s[2] + dst[15] * s[3];
	t[4] = dst[0] * s[4] + dst[4] * s[5] + dst[8] * s[6] + dst[12] * s[7];
	t[5] = dst[1] * s[4] + dst[5] * s[5] + dst[9] * s[6] + dst[13] * s[7];
	t[6] = dst[2] * s[4] + dst[6] * s[5] + dst[10] * s[6] + dst[14] * s[7];
	t[7] = dst[3] * s[4] + dst[7] * s[5] + dst[11] * s[6] + dst[15] * s[7];
	t[8] = dst[0] * s[8] + dst[4] * s[9] + dst[8] * s[10] + dst[12] * s[11];
	t[9] = dst[1] * s[8] + dst[5] * s[9] + dst[9] * s[10] + dst[13] * s[11];
	t[10] = dst[2] * s[8] + dst[6] * s[9] + dst[10] * s[10] + dst[14] * s[11];
	t[11] = dst[3] * s[8] + dst[7] * s[9] + dst[11] * s[10] + dst[15] * s[11];
	t[12] = dst[0] * s[12] + dst[4] * s[13] + dst[8] * s[14] + dst[12] * s[15];
	t[13] = dst[1] * s[12] + dst[5] * s[13] + dst[9] * s[14] + dst[13] * s[15];
	t[14] = dst[2] * s[12] + dst[6] * s[13] + dst[10] * s[14] + dst[14] * s[15];
	t[15] = dst[3] * s[12] + dst[7] * s[13] + dst[11] * s[14] + dst[15] * s[15];
	matrix_copy(dst, (float*)t);
	return (dst);
}