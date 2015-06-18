/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 13:33:53 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/10 14:21:38 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_point3	new_point3(int x, int y, int z)
{
	t_point3	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

int			point3_dist(t_point3 p1, t_point3 p2)
{
	int	xx;
	int	yy;
	int	zz;

	xx = (p2.x - p1.x) * (p2.x - p1.x);
	yy = (p2.y - p1.y) * (p2.y - p1.y);
	zz = (p2.z - p1.z) * (p2.z - p1.z);
	return (sqrt(xx + yy + zz));
}

t_point3	to_point3(t_vec3 vec)
{
	return (new_point3((int)vec.x, (int)vec.y, (int)vec.z));
}