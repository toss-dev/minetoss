/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 00:09:08 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/06 19:37:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int 	mod(int value, int modulus)
{
	return (value % modulus + modulus) % modulus;
}

static int 	intbound(float s, float ds)
{
	if (ds < 0)
		return (intbound(-s, -ds));
	s = mod(s, 1);
	return ((1 - s) / ds);
}

void		raycast(t_vec3 origin, t_vec3 direction, float radius, int (*callback)(), void *extra)
{
	t_vec3	face;
	t_vec3	step;
	t_vec3	max;
	t_vec3	delta;
	t_vec3	pos;

	pos.x = floor(origin.x);
	pos.y = floor(origin.y);
	pos.z = floor(origin.z);
	
	step.x = SIGN(direction.x);
	step.y = SIGN(direction.y);
	step.z = SIGN(direction.z);

	max.x = intbound(origin.x, direction.x);
	max.y = intbound(origin.y, direction.y);
	max.z = intbound(origin.z, direction.z);

	delta.x = step.x / direction.x;
	delta.y = step.y / direction.y;
	delta.z = step.z / direction.z;

	while (1)
	{
		if (callback(extra, pos, face))
		{
			return ;
		}

    	if (max.x < max.y)
    	{
    		if (max.x < max.z)
     		{
     			if (max.x > radius)
        			break;
        		pos.x += step.x;
	       		max.x += delta.x;
	        	face.x = -step.x;
	        	face.y = 0;
	        	face.z = 0;
	      	}
	      	else
	      	{
	      		if (max.z > radius)
        			break;
	        	pos.z += step.z;
	        	max.z += delta.z;
	        	face.x = 0;
	        	face.y = 0;
	        	face.z = -step.z;
	     	}
    	}
    	else
    	{
    		if (max.y < max.z)
    		{
    			if (max.y > radius)
    				break;
        		pos.y += step.y;
        		max.y += delta.y;
        		face.x = 0;
        		face.y = -step.y;
        		face.z = 0;
      		}
      		else
      		{
      			if (max.z > radius)
      				break;
      			pos.z += step.z;
      			max.z += delta.z;
      			face.x = 0;
      			face.y = 0;
      			face.z = -step.z;
      		}
      	}
	}
}
