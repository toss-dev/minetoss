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
	char 		blocks[TERRAIN_SIZEX][TERRAIN_SIZEY][TERRAIN_SIZEZ];
	t_point3	index;	//given x, y, z index (for hashtable)
}				t_terrain;

enum 			e_thread_id
{
	THRD_NETWORK,
	THRD_MAX
};

enum 			e_game_state
{
	GAME_STATE_RUNNING = 1
};

typedef struct 	s_game
{
	pthread_t	threads[THRD_MAX];
	t_server	*server;
	int 		state;
}				t_game;

/** network*/
void	gameNetworkInit(t_game *game);
void	gameNetworkStart(t_game *game);
void	gameNetworkStop(t_game *game);

/** game */
void	gameInit(t_game *game);
void	gameLoop(t_game *game);
void	gameStart(t_game *game);
void	gameStop(t_game *game);

int 	isGameRunning(t_game *game);

/** packets*/
void	packetHandlerConnection(t_game *game, SOCKADDR_IN *sockaddr);

#endif