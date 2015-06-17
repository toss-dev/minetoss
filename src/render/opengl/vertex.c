/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 02:26:08 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/05 02:28:45 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vertex	new_vertex(t_vec3 pos, t_vec3 normal, t_vec2 uv)
{
	t_vertex	vertex;

	vertex.pos = pos;
	vertex.normal = normal;
	vertex.uv = uv;
	return (vertex);
}

void		vertex_to_float_buffer(float buffer[3 + 3 + 2], t_vertex *vertex)
{
	memcpy(buffer, vertex, sizeof(t_vertex));
}