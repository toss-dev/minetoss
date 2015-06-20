/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 22:00:19 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/06 22:02:01 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	renderTime(t_renderer *renderer)
{
		(void)renderer;

	char			buffer[64];
	t_font_model	model;
	int 			current;

	current = (int) (renderer->timer->tick_ratio * TICK_PER_CYCLE);
	sprintf(buffer, "day time: %d/%d", current, TICK_PER_CYCLE);
	model = generateFontModel(buffer, new_vec3(1, 0, 0), new_vec3(0, 0, 0), 0);
	setFontModelPosition(&model, new_vec3(1 - getFontStringWidth(&model, buffer), 0.90f, -0.28f));
	renderFont(renderer->programs + PROGRAM_FONT, &model);
	deleteFontModel(&model);
}

static void	renderFps(t_renderer *renderer)
{
	(void)renderer;
	char			buffer[64];
	t_font_model	model;

	sprintf(buffer, "%u fps", renderer->fps);
	model = generateFontModel(buffer, new_vec3(1, 0, 0), new_vec3(-0.95f, 0.90f, 0), -0.2f);
	renderFont(renderer->programs + PROGRAM_FONT, &model);
	deleteFontModel(&model);
}

void	renderUI(t_world *world, t_renderer *renderer)
{	
	if (rendererHasConfig(renderer, RENDERER_CONFIG_DEBUG))
	{
		renderFps(renderer);
		renderTime(renderer);
	}

	(void)world;
}
