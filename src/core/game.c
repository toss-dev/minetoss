/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/14 14:02:06 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/14 14:02:15 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	isGameRunning(t_game *game)
{
	return (game->state & GAME_STATE_RUNNING);
}

void	gameStop(t_game *game)
{
	game->state = game->state & ~(GAME_STATE_RUNNING);
}

void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid *userParam)
{
	(void)source;
	(void)type;
	(void)id;
	(void)severity;
	(void)length;
	(void)userParam;
	(void)source;
	(void)source;
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            printf("error: %s\n", message);
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            printf("deprecated: %s\n", message);
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            printf("undefined: %s\n", message);
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            printf("portability: %s\n", message);
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            printf("performance: %s\n", message);
            break;
        case GL_DEBUG_TYPE_OTHER:
            printf("other: %s\n", message);
            break;
        case GL_DEBUG_TYPE_MARKER:
            printf("marker: %s\n", message);
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            printf("push_group: %s\n", message);
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            printf("pop_group: %s\n", message);
            break;
    }
}

t_game	*gameNew(void)
{
	t_game	*game;

	logger_log(LOG_FINE, "Creating new game ...");
	if ((game = malloc(sizeof(t_game))) == NULL)
	{
		logger_log(LOG_FINE, "Not enough memory for game.");
		return (NULL);
	}
	memset(game, 0, sizeof(t_game));
	initWindow(&(game->window));
	initEvent(&(game->window));
	initRenderer(&(game->renderer));
	initWorld(&(game->world));
	initTimer(&(game->timer));
	glhCheckError("Game initialization");

	glDebugMessageCallbackARB((GLDEBUGPROC)DebugCallback, NULL);
	return (game);
}
