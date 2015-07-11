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

void		gameNetworkInit(t_game *game)
{
	game->server = srvStart(4242);
}

static void	gamePacketHandlerConnection(t_game *game, t_client_packet *packet, SOCKADDR_IN *sockaddr)
{
	(void)game;
	(void)packet;
	(void)sockaddr;
}

static void	gameNetworkPacketHandler(t_game *game, t_client_packet *cp, SOCKADDR_IN *sockaddr)
{
	t_function	packet_handler[PACKET_ID_MAX] = {
		gamePacketHandlerConnection
	};

	if (cp->packet.header.id >= PACKET_ID_MAX)
	{
		logger_log(LOG_WARNING, "Received an unknown packet id!");
		return ;
	}
	packet_handler[cp->packet.header.id](game, cp, sockaddr);
	logger_log(LOG_FINE, "Server received packet: id: %d size: %d\n", cp->packet.header.id, cp->packet.header.size);

	(void)game;
	(void)sockaddr;
}

//thread network main function
static void	gameNetworkStartLoop(t_game *game)
{
	t_client_packet	packet;
	SOCKADDR_IN		sockaddr;

	while (isGameRunning(game))
	{
		if (srvPacketReceive(game->server, &packet, &sockaddr, 1, 0) > 0)
		{
			gameNetworkPacketHandler(game, &packet, &sockaddr);
		}
	}
	pthread_exit(EXIT_SUCCESS);
}

/** one thread is created here and will loop reading packets, the other one exit the function */
void		gameNetworkStart(t_game *game)
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