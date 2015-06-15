/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 23:19:25 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/12 18:03:40 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void loadQuadRenderer(t_renderer *renderer)
{
	t_vertex	buffer[] = {
		{{-1, 1, 0}, {0, 1, 0}, {0, 0}},
		{{-1, -1, 0}, {0, 1, 0}, {0, 1}},
		{{1, -1, 0}, {0, 1, 0}, {1, 1}},
		{{-1, 1, 0}, {0, 1, 0}, {0, 0}},
		{{1, -1, 0}, {0, 1, 0}, {1, 1}},
		{{1, 1, 0}, {0, 1, 0}, {1, 0}}
	};

	renderer->quad_model = new_model(GL_STATIC_DRAW);
	initModel(&(renderer->quad_model), buffer, sizeof(buffer) / sizeof(t_vertex));
}

void	initRenderer(t_renderer *renderer)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glfwSwapInterval(0);
	glhSetContext(&(renderer->context));
	logger_log(LOG_FINE, "Loading renderer...");
	{
		logger_log(LOG_FINE, "Loading simple quad for UI and particles");
		loadQuadRenderer(renderer);
		logger_log(LOG_FINE, "Loading blocks...");
		loadBlocks(renderer);
		logger_log(LOG_FINE, "Loading programs...");
		loadPrograms(renderer);
		logger_log(LOG_FINE, "Loading camera...");
		loadCamera(renderer);
		logger_log(LOG_FINE, "Loading mesh renderer...");
		loadTerrainMeshFactory(renderer);
		logger_log(LOG_FINE, "Loading particles...");
		loadParticles(renderer);
		logger_log(LOG_FINE, "Loading particles textures...");
		loadParticleTextures(renderer);
		logger_log(LOG_FINE, "Loading sky...");
		loadSky(renderer);
	}
	logger_log(LOG_FINE, "Renderer loaded.");
}

/**
**	Main rendering function (write render data to default frame color and depth buffer)
*/
void		render(t_world *world, t_renderer *renderer)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderSky(world, renderer);
	renderTerrains(world, renderer);
	renderParticles(world, renderer);
	renderUI(world, renderer);
}
