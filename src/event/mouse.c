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

bool	g_press = false;

static int	raycastCallback(t_world *world, t_vec3 pos, t_vec3 face)
{
	unsigned	blockID;

	blockID = getBlock(world, pos);
	if (blockID == BLOCK_AIR)
	{
		setBlock(world, BLOCK_PACKED_ICE, pos);
		return (1);
	}
	(void)face;
	return (0);
}


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
		g_press = (action == GLFW_RELEASE) ? false : (action == GLFW_PRESS);
		if (g_press == false)
		{
			raycast(vec3_add(g_game->renderer.camera.pos, new_vec3(0, 0.5f, 0)), g_game->renderer.camera.look_vec, 128, raycastCallback, &(g_game->world));
		}
	}
	(void)window;
	(void)mods;
	(void)action;
	(void)button;
}
