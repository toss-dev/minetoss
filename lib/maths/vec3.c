/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 13:33:53 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/10 14:21:38 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

double	vec3_square_dist(t_vec3 v1, t_vec3 v2)
{
	double	xx;
	double	yy;
	double	zz;

	xx = (v2.x - v1.x) * (v2.x - v1.x);
	yy = (v2.y - v1.y) * (v2.y - v1.y);
	zz = (v2.z - v1.z) * (v2.z - v1.z);
	return (xx + yy + zz);
}

double	vec3_dist(t_vec3 v1, t_vec3 v2)
{
	return (vec3_square_dist(v1, v2));
}

int		vec3_equals(t_vec3 v1, t_vec3 v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

t_vec3	new_vec3(float x, float y, float z)
{
	t_vec3	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}


t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec3	vec3_multiply(t_vec3 a, double r)
{
	t_vec3	ret;

	ret.x = a.x * r;
	ret.y = a.y * r;
	ret.z = a.z * r;
	return (ret);
}

double	vec3_dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	ret;

	ret.x = a.y * b.z - b.y * a.z;
	ret.y = a.z * b.x - b.z * a.x;
	ret.z = a.x * b.y - b.x * a.y;
	return (ret);
}

double	vec3_square_norm(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	vec3_norm(t_vec3 vec)
{
	return (sqrt(vec3_square_norm(vec)));
}

t_vec3	vec3_normalize(t_vec3 vec)
{
	double	norm;

	norm = vec3_norm(vec);
	vec.x = vec.x / norm;
	vec.y = vec.y / norm;
	vec.z = vec.z / norm;
	return (vec);
}

t_vec3	to_vec3(t_point3 p)
{
	return (new_vec3((float)p.x, (float)p.y, p.z));
}