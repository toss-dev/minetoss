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

#include "client/main.h"

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

/** load every game textures (except blocks texture) */
static void	loadTextures(t_renderer *renderer)
{
	renderer->textures[T_GUI_BUTTON_PRESSED] = glhLoadTexture("gui/button_pressed.png");
	renderer->textures[T_GUI_BUTTON_RELEASED] = glhLoadTexture("gui/button_released.png");
	renderer->textures[T_GUI_BUTTON_HOVERED] = glhLoadTexture("gui/button_hovered.png");
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
	glfwSwapInterval(1);
	renderer->config = 0;
	renderer->views_list = list_new();
	logger_log(LOG_FINE, "Loading renderer...");
	{
		logger_log(LOG_FINE, "Loading font...");
		loadFont();

		logger_log(LOG_FINE, "Loading simple quad for UI and particles");
		loadQuadRenderer(renderer);

		logger_log(LOG_FINE, "Loading views");
		loadViews(renderer);

		logger_log(LOG_FINE, "Loading textures");
		loadTextures(renderer);

		logger_log(LOG_FINE, "Loading blocks...");
		loadBlocks(renderer);

		logger_log(LOG_FINE, "Loading programs...");
		loadPrograms(renderer);

		logger_log(LOG_FINE, "Loading camera...");
		loadCamera(renderer);

		logger_log(LOG_FINE, "Loading mesh renderer...");
		loadTerrainMeshFactory(renderer);

		logger_log(LOG_FINE, "Loading sky...");
		loadSky(renderer);
	}
	logger_log(LOG_FINE, "Renderer loaded.");
}

void	rendererAddView(t_renderer *renderer, unsigned int viewID)
{
	list_add(&(renderer->views_list), &viewID, sizeof(unsigned int));
}

static int	rendererViewCmp(unsigned int *lst_viewID, unsigned int *ref_viewID)
{
	if (*lst_viewID == *ref_viewID)
	{
		return (0);
	}
	return (1);
}

void	rendererRemoveView(t_renderer *renderer, unsigned int viewID)
{
	list_remove(&(renderer->views_list), NULL, (t_cmp_func)rendererViewCmp, &viewID);
}

t_view	*rendererGetView(t_renderer *renderer, unsigned int viewID)
{
	return (renderer->views + viewID);
}

/**
**	Main rendering function (write render data to default frame color and depth buffer)
*/
void	render(t_game *game)
{
	t_renderer	*renderer;

	renderer = &(game->renderer);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameHasState(game, GAME_INGAME))
	{
		renderIngame(game);
	}
	else if (gameHasState(game, GAME_MAIN_MENU))
	{
		renderMainMenu(game);
	}

	LIST_ITER_START(renderer->views_list, int, viewID);
	{
		renderView(renderer, rendererGetView(renderer, *viewID));
	}
	LIST_ITER_END(renderer->views_list, t_view, view)
}
