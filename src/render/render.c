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
	t_vertex	quad_vertex[] = {
		{{-1, 1, 0}, {0, 1, 0}, {0, 0}},
		{{-1, -1, 0}, {0, 1, 0}, {0, 1}},
		{{1, -1, 0}, {0, 1, 0}, {1, 1}},
		{{-1, 1, 0}, {0, 1, 0}, {0, 0}},
		{{1, -1, 0}, {0, 1, 0}, {1, 1}},
		{{1, 1, 0}, {0, 1, 0}, {1, 0}}
	};

	renderer->quad_model = new_model(GL_STATIC_DRAW);
	setModelVertices(&renderer->quad_model, ft_memdup(quad_vertex, sizeof(quad_vertex)), 6);
}

/** enable the config */
void rendererActiveConfig(t_renderer *renderer, unsigned config)
{
	renderer->config = renderer->config | config;
}

/** disable the config */
void rendererDisableConfig(t_renderer *renderer, unsigned config)
{
	renderer->config = renderer->config & ~(config);
}

/** enable the config if it is disable, or disable it */
void rendererSwitchConfig(t_renderer *renderer, unsigned config)
{
	renderer->config = renderer->config ^ config;
}

/** check if the given config is enable */
int rendererHasConfig(t_renderer *renderer, unsigned config)
{
	return (renderer->config & config);
}

/** called once at initialization, intialize every rendering thingies */
void	initRenderer(t_renderer *renderer)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glfwSwapInterval(1);
	renderer->config = 0;
	logger_log(LOG_FINE, "Loading renderer...");
	{
		logger_log(LOG_FINE, "Loading font...");
		loadFont();
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

	(void)world;
}
