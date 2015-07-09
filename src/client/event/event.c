/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 23:23:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/02 23:24:08 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

void	initEvent(t_window *window)
{
	glfwSetKeyCallback(window->ptr, keyCallback);
	glfwSetCursorPosCallback(window->ptr, cursorMoveCallback);
	glfwSetMouseButtonCallback(window->ptr, mouseButtonCallback);
	glfwSetInputMode(window->ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window->ptr, (int)(WIDTH / 2), (int)(HEIGHT / 2));
}
