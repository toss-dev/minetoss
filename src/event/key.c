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

# define KEY_CALLBACKS_MAX 2

void	keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	static t_key_callback	callbacks[KEY_CALLBACKS_MAX] = {
		{GLFW_KEY_R, GLFW_RELEASE, keyDebugCallback},
		{GLFW_KEY_ESCAPE, GLFW_PRESS, keyNotifyClose}
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