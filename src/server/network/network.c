/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/main.h"

void		gameNetworkStart(t_game *game)
{
	game->server = srvStart(4242);
}

static void	gameNetworkPacketHandler(t_game *game, t_packet *packet, SOCKADDR_IN *sin)
{
	if (packet->header.id < 0 || packet->header.id >= PACKET_ID_MAX)
	{
		logger_log(LOG_WARNING, "Received an unknown packet id!");
		return ;
	}
	logger_log(LOG_FINE, "Server received packet: id: %d size: %d\n", packet->header.id, packet->header.size);

	(void)game;
	(void)sin;
}

//thread network main function
static void	gameNetworkStartLoop(t_game *game)
{
	t_packet    packet;
	SOCKADDR_IN	sin;

	while (isGameRunning(game))
	{
		if (packetReceive(game->server->sock, &sin, 1, 0, &packet) > 0)
		{
			gameNetworkPacketHandler(game, &packet, &sin);
		}
	}
	pthread_exit(EXIT_SUCCESS);
}

/** one thread is created here and will loop reading packets, the other one exit the function */
void		gameNetworkInit(t_game *game)
{
	if (pthread_create(game->threads + THRD_NETWORK, NULL, (t_pthread_start)gameNetworkStartLoop, game) != 0)
	{
		logger_log(LOG_ERROR, "Couldnt start network thread");
		exit(EXIT_FAILURE);
	}
}

void 		gameNetworkStop(t_game *game)
{
	srvStop(game->server);
}