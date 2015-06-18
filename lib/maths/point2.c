/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 13:33:53 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/10 14:21:38 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_point2	new_point2(int x, int y)
{
	t_point2	p;

	p.x = x;
	p.y = y;
	return (p);
}

int			point2_dist(t_point2 p1, t_point2 p2)
{
	int	xx;
	int	yy;

	xx = (p2.x - p1.x) * (p2.x - p1.x);
	yy = (p2.y - p1.y) * (p2.y - p1.y);
	return (sqrt(xx + yy));
}

t_point2	to_point2(t_vec2 vec)
{
	return (new_point2((int)vec.x, (int)vec.y));
}