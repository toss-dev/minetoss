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

#include "client/main.h"

int	g_press = 0;
double g_mouse_x = 0;
double g_mouse_y = 0;

static void	mouseViewEvent(t_game *game, t_view_event_funct callback)
{
	t_view	*view;
	float 	x;
	float 	y;
	int 	width;
	int 	height;

	glfwGetWindowSize(game->window.ptr, &(width), &(height));
	x = g_mouse_x / (float)width;
	y = g_mouse_y / (float)height;

	LIST_ITER_START(game->renderer.views_list, int, viewID)
	{
		view = rendererGetView(&(game->renderer), *viewID);
		if ((x >= view->pos.x && x <= view->pos.x + view->size.x)
			&& (y >= view->pos.y && y <= view->pos.y + view->size.y))
		{
			callback(view, x, y);
		}
	}
	LIST_ITER_END(game->renderer.views_list, t_view, view);
}

static void	moveCamera(GLFWwindow *window, double x, double y)
{
	static double	prevx = 0;
	static double	prevy = 0;
	float const 	speed = 0.005f;

	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
	{
		return ;
	}

	if (prevx != 0 || prevy != 0)
	{
		g_game->renderer.camera.yaw += (x - prevx) * speed;
		g_game->renderer.camera.pitch += (y - prevy) * speed;
	}

	prevx = x;
	prevy = y;
}

/** called by glfw whenever the mouse is moved */
void	cursorMoveCallback(GLFWwindow *window, double x, double y)
{
	g_mouse_x = x;
	g_mouse_y = y;
	mouseViewEvent(g_game, viewOnMouseHover);
	moveCamera(window, x, y);
}

void	mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == 0)
	{
		g_press = (action == GLFW_RELEASE) ? 0 : (action == GLFW_PRESS);
		mouseViewEvent(g_game, (g_press) ? viewOnMousePressed : viewOnMouseReleased);

		/*
		if (g_press == 0)
		{
			//set a block on click
			t_vec3	pos;

			pos = vec3_add(vec3_add(g_game->renderer.camera.pos, vec3_multiply(g_game->renderer.camera.look_vec, 4)), new_vec3(0.5f, 0.5f, 0.5f));
			setBlock(&(g_game->world), BLOCK_PACKED_ICE, pos);
		}
		*/
	}
	(void)window;
	(void)mods;
}
