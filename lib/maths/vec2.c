/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 15:46:29 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/11 16:02:00 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	new_vec2(float x, float y)
{
	t_vec2	p;
	
	p.x = x;
	p.y = y;
	return (p);
}

double	vec2_dist(t_vec2 a, t_vec2 b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

double 	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

double	vec2_dot_product(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

t_vec2	to_vec2(t_point2 p)
{
	return (new_vec2((float)p.x, (float)p.y));
}

t_vec2	vec2_multiply(t_vec2 a, double r)
{
	t_vec2	ret;

	ret.x = a.x * r;
	ret.y = a.y * r;
	return (ret);
}