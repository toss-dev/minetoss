/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:43:08 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/28 15:16:35 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	updateMove(t_particle *particle)
{
	particle->pos = vec3_add(particle->pos, particle->pos_vec);
	if (particle->timer % 6 == 0)
	{
		particle->texture_atlas_id++;
	}
}

static void	updateParticle(t_particle *particle, t_renderer *renderer, int idx)
{
	static t_function	f_update[PARTICLES_MAX_TYPE] = {
		updateMove
	};
	if (f_update[particle->id] != NULL)
	{
		f_update[particle->id](particle);
	}
	if (particle->health <= 0)
	{
		array_list_remove(&(renderer->particles), idx);
		return ;
	}
	particle->health--;
	particle->timer++;
	particle->camera_dist = vec3_dist(renderer->camera.pos, particle->pos);
}

void		updateParticles(t_renderer *renderer)
{
	array_list_iter(renderer->particles, (t_iter_array_function)updateParticle, renderer);
}