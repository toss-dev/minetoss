/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 19:51:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 15:13:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	cameraControlRelease(t_camera *camera, int key)
{
	if (key == GLFW_KEY_UP|| key == GLFW_KEY_DOWN)
		camera->vec_rot = new_vec3(0, 0, 0);
	else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT)
		camera->vec_rot = new_vec3(0, 0, 0);
	else if (key == GLFW_KEY_W)
		camera->state &= ~(C_MOVE_FORWARD);
	else if (key == GLFW_KEY_S)
		camera->state &= ~(C_MOVE_BACKWARD);
	else if (key == GLFW_KEY_A)
		camera->state &= ~(C_MOVE_LEFT);
	else if (key == GLFW_KEY_D)
		camera->state &= ~(C_MOVE_RIGHT);
	//else if (key == GLFW_KEY_LEFT_SHIFT)
	//	camera->vec_pos.y = 0;
}

void	cameraControlPress(t_camera *camera, int key)
{
	if (key == GLFW_KEY_S)
		camera->state |=  C_MOVE_BACKWARD;
	else if (key == GLFW_KEY_W)
		camera->state |= C_MOVE_FORWARD;
	else if (key == GLFW_KEY_A)
		camera->state |= C_MOVE_LEFT;
	else if (key == GLFW_KEY_D)
		camera->state |= C_MOVE_RIGHT;
	else if (key == GLFW_KEY_UP)
		camera->vec_rot = new_vec3(-1, 0, 0);
	else if (key == GLFW_KEY_DOWN)
		camera->vec_rot = new_vec3(1, 0, 0);
	else if (key == GLFW_KEY_LEFT)
		camera->vec_rot = new_vec3(0, -1, 0);
	else if (key == GLFW_KEY_RIGHT)
		camera->vec_rot = new_vec3(0, 1, 0);
	//else if (key == GLFW_KEY_LEFT_SHIFT)
	//	camera->vec_pos.y = -1;
}
