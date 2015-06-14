/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_uniforms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 09:39:19 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/02 23:41:37 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	loadUniformMatrix(GLuint id, float *matrix)
{
	glUniformMatrix4fv(id, 1, GL_TRUE, matrix);
}

void	loadUniformFloat(GLuint id, float value)
{
	glUniform1f(id, value);
}

void	loadUniformVec(GLuint id, t_vec3 p)
{
	glUniform3f(id, p.x, p.y, p.z);
}

void	loadUniformInt(GLuint id, GLuint integer)
{
	glUniform1i(id, integer);
}