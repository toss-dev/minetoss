/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/23 12:37:38 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 17:34:01 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
/*
static void	test_explosion_particle(t_renderer *renderer)
{
	int i;

	for (i = 0 ; i < PARTICLES_MAX ; i++)
	{
		t_particle p = new_particle(renderer->camera.pos,
							new_vec3(0.5f, 0.5f, 0.5f),
							new_vec3(0, 0, 0),
							new_vec3(0.5f, 0, 0),
							ParticleMoving, T_ATLAS_EXPLOSION, 40);
		p.pos_vec.x = rand_float_in_range(-1, 1);
		p.pos_vec.y = rand_float_in_range(-1, 1);
		p.pos_vec.z = rand_float_in_range(-1, 1);
		p.pos_vec = vec3_normalize(p.pos_vec);
		addParticle(renderer, p);
	}
}
*/

void	keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_R)
		{
			//test_explosion_particle(&(g_game->renderer));
		}
		cameraControlRelease(&(g_game->renderer.camera), key);
	}
	else if (action == GLFW_PRESS)
	{
		cameraControlPress(&(g_game->renderer.camera), key);
	}
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	(void)scancode;
	(void)mods;
}