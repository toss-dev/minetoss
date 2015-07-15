/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 00:05:11 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/03 00:06:01 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "common/common.h"
# include "server/network/server.h"

typedef struct 	s_terrain	//16x256x16
{
	t_terrain_data	data;
	unsigned int 	state;
}				t_terrain;

enum 			e_thread_id
{
	THRD_NETWORK,
	THRD_TERRAIN_GENERATOR,
	THRD_TERRAIN_SENDER,
	THRD_MAX
};

typedef struct 	s_world
{
	t_htab		terrains;
	t_list 		entities;
	t_weather	weather;
	t_timer		*timer;	//pointer to the main game timer
}				t_world;

enum 			e_game_state
{
	GAME_STATE_RUNNING = 1
};

typedef struct 	s_game
{
	pthread_t	threads[THRD_MAX];
	t_server	*server;
	t_world		world;
	t_timer		timer;	//main game timer
	int 		state;
}				t_game;

/** network*/
void	networkInit(t_game *game);
void	networkStart(t_game *game);
void	networkStop(t_game *game);

/** game */
void	gameInit(t_game *game);
void	gameLoop(t_game *game);
void	gameStart(t_game *game);
void	gameStop(t_game *game);

int 	isGameRunning(t_game *game);

/** world generator */
void 	startTerrainUpdate(t_game *game);
void	startWorldGenerator(t_game *game);
void   	generateTerrain(t_terrain *terrain);
void	loadWorldGenerator(void);
void	prepareNoise(void);
double	noise2(t_vec2 in);
double	noise3(t_vec3 in);

/** server packet handler */
void	packetHandlerLive(t_game *game, t_server_packet *packet);

#endif