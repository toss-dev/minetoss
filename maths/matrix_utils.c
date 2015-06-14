/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 17:47:57 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/06 17:08:57 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

void	matrix_identity(float *m)
{
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = 0;
	m[5] = 1;
	m[6] = 0;
	m[7] = 0;
	m[8] = 0;
	m[9] = 0;
	m[10] = 1;
	m[11] = 0;
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

void	matrix_copy(float *dst, float *src)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = src[3];
	dst[4] = src[4];
	dst[5] = src[5];
	dst[6] = src[6];
	dst[7] = src[7];
	dst[8] = src[8];
	dst[9] = src[9];
	dst[10] = src[10];
	dst[11] = src[11];
	dst[12] = src[12];
	dst[13] = src[13];
	dst[14] = src[14];
	dst[15] = src[15];
}

float	*new_matrix(void)
{
	float	*matrix;

	matrix = (float*)malloc(sizeof(float) * 16);
	if (matrix == NULL)
		return (NULL);
	matrix_identity(matrix);
	return (matrix);
}

void	matrix_inverse(float *matrix)
{
	float	tmp[16];
	int		i;
	int		j;

	i = 0;
	memcpy(tmp, matrix, sizeof(float) * 16);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix[i * 4 + j] = tmp[i + j * 4];
			j++;
		}
		i++;
	}
}
