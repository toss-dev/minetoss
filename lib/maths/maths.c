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

int		fastfloor(double x)
{
    int xi;

    xi = (int)x;
    return (x < xi) ? (xi - 1) : xi;
}


float	clamp(float val, float min, float max)
{
    return (MAX(min, MIN(max, val)));
}
