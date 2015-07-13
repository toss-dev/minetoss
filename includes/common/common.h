/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "common/network.h"
# include "common/blocks.h"
# include "common/const.h"
# include "common/timer.h"
# include "maths.h"
# include "libft.h"
# include <pthread.h>

typedef struct	s_entity
{
	t_vec3	rot;
	t_vec3	scale;
	t_vec3	pos;
	t_vec3	rot_vec;
	t_vec3	scale_vec;
	t_vec3	pos_vec;
	int		textureID;
	float	health;
	float 	speed;
}				t_entity;

typedef struct 	s_weather
{
	t_vec3	sun_pos;
	t_vec3	sun_color;
	t_vec3	fog_color;
	float 	fog_density;
	float 	fog_gradient;
}				t_weather;

typedef struct 	s_world
{
	t_timer			*timer;
	t_htab			terrains;
	t_weather		weather;
	t_array_list	terrain_garbage;	//array list of t_point3, remove chunks at these coordinates
}				t_world;

#endif
