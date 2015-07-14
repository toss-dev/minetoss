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

#include "client/main.h"

typedef struct 	s_key_callback
{
	int		key;
	int		action;
	void	(*f)(t_game *);
}				t_key_callback;

static void	keyDebugCallback(t_game *game)
{
	rendererSwitchConfig(&(game->renderer), RENDERER_CONFIG_DEBUG);
}

static void	keyNotifyClose(t_game *game)
{
	glfwSetWindowShouldClose(game->window.ptr, GL_TRUE);
}

static void	keyToggleCursor(t_game *game)
{
	if (glfwGetInputMode(game->window.ptr, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		glfwSetInputMode(game->window.ptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(game->window.ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	glfwSetCursorPos(game->window.ptr, (int)(WIDTH / 2), (int)(HEIGHT / 2));
}

# define KEY_CALLBACKS_MAX 3

void	keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	static t_key_callback	callbacks[KEY_CALLBACKS_MAX] = {
		{GLFW_KEY_R, GLFW_RELEASE, keyDebugCallback},
		{GLFW_KEY_ESCAPE, GLFW_PRESS, keyNotifyClose},
		{GLFW_KEY_T, GLFW_RELEASE, keyToggleCursor}
	};
	unsigned	i;

	for (i = 0 ; i < KEY_CALLBACKS_MAX ; i++)
	{
		if (callbacks[i].key == key && callbacks[i].action == action)
		{
			callbacks[i].f(g_game);
			return ;
		}
	}

	if (action == GLFW_RELEASE)
	{
		cameraControlRelease(&(g_game->renderer.camera), key);
	}
	else if (action == GLFW_PRESS)
	{
		cameraControlPress(&(g_game->renderer.camera), key);
	}

	(void)scancode;
	(void)mods;
	(void)window;
}
