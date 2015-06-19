/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 15:07:20 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/28 15:27:24 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
**		0		3	|	(0, 0)	(1, 0)	|	(-1,  1, 0)		(1, 1, 0)
**
**		1		2	|	(0, 1)	(1, 1)	|	(-1, -1, 0)		(1, -1, 0)
*/

void 	loadParticles(t_renderer *renderer)
{
	renderer->particles = array_list_new(PARTICLES_MAX, sizeof(t_particle));
}

t_particle	new_particle(t_vec3 pos, t_vec3 scal, t_vec3 rot, t_vec3 color,
						int id, GLuint texture_id, float life)
{
	t_particle	particle;

	particle.pos = pos;
	particle.scale = scal;
	particle.rot = rot;
	particle.pos_vec = new_vec3(0, 0, 0);
	particle.scale_vec = new_vec3(0, 0, 0);
	particle.rot_vec = new_vec3(0, 0, 0);
	particle.id =  id;
	particle.texture_id = texture_id;
	particle.health = life;
	particle.speed = 1;
	particle.color = color;
	particle.texture_atlas_id = 0;
	particle.timer = 0;
	return (particle);
}

void		addParticle(t_renderer *renderer, t_particle particle)
{
	array_list_add(&(renderer->particles), &particle);
}
