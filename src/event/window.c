/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 13:45:19 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 17:21:25 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	prepare_window(void)
{
	#ifdef __APPLE__
		logger_log(LOG_FINE, "Setting apple window hint");
		glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  		glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
  		glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  		glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif
}

static void	prepare_glew(void)
{
	# ifdef _WIN32
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			logger_log(LOG_ERROR, "Couldnt initialize glew: %s", glewGetErrorString(err));
			exit(EXIT_FAILURE);
		}
	# endif
}

void 	cleanWindow(t_window *window)
{
	glfwDestroyWindow(window->ptr);
	(void)window;
}

void	initWindow(t_window *window)
{
	logger_log(LOG_FINE, "Initializing window");
	if (!glfwInit())
	{
		logger_log(LOG_ERROR, "Couldnt initialized glfw");
		exit(EXIT_FAILURE);
	}
	prepare_window();
	window->ptr = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (window->ptr == NULL)
    {
    	logger_log(LOG_ERROR, "Couldnt open window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
	glfwMakeContextCurrent(window->ptr);
	prepare_glew();
	logger_log(LOG_FINE, "Window initialized");
}