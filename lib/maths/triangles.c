/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 22:19:54 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 22:40:29 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

float	barrycentric(t_vec3 p1, t_vec3 p2, t_vec3 p3, t_vec2 pos)
{
	float	det;
	float	l1;
	float	l2;
	float	l3;

	det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	l3 = 1.0f - l1 - l2;
	return (l1 * p1.y + l2 * p2.y + l3 * p3.y);
}
