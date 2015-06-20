/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/23 11:25:38 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 18:26:43 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_press = 0;

void	cursorMoveCallback(GLFWwindow *window, double x, double y)
{
	static double	prevx = 0;
	static double	prevy = 0;
	float const 	speed = 0.005f;

	if (prevx != 0 || prevy != 0)
	{
		g_game->renderer.camera.yaw += (x - prevx) * speed;
		g_game->renderer.camera.pitch += (y - prevy) * speed;
	}

	prevx = x;
	prevy = y;
	(void)window;
}

void	mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == 0)
	{
		g_press = (action == GLFW_RELEASE) ? 0 : (action == GLFW_PRESS);
		if (g_press == 0)
		{
			t_vec3	pos;

			pos = vec3_add(vec3_add(g_game->renderer.camera.pos, vec3_multiply(g_game->renderer.camera.look_vec, 4)), new_vec3(0.5f, 0.5f, 0.5f));
			setBlock(&(g_game->world), BLOCK_PACKED_ICE, pos);
		}
	}
	(void)window;
	(void)mods;
	(void)action;
	(void)button;
}
