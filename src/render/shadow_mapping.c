/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 15:48:50 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/24 14:52:54 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	loadShadowMapping(t_renderer *renderer)
{
	(void)renderer;
	return ;

	/*
	renderer->shadow_fbo = glhGenFBO();
	glBindFramebuffer(GL_FRAMEBUFFER, renderer->shadow_fbo);
	
	glGenTextures(1, &(renderer->shadow_depth_texture));
	glBindTexture(GL_TEXTURE_2D, renderer->shadow_depth_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, renderer->shadow_depth_texture, 0);

	glDrawBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		logger_log("Cant create shadow mapping framebuffer.", 2, LOG_ERROR, 1);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	renderer->shadow_proj_matrix = new_matrix();
*/


}
