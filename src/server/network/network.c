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

static void	gameNetworkPacketHandler(t_game *game, t_client_packet *cp, SOCKADDR_IN *sockaddr)
{
	static t_function	packet_handler[PACKET_ID_MAX] = {
		packetHandlerConnection
	};

	if (cp->packet.header.id >= PACKET_ID_MAX)
	{
		logger_log(LOG_WARNING, "Received an unknown packet id!");
		return ;
	}

	if (cp->packet.header.id == PACKET_ID_CONNECTION)
	{
		packetHandlerConnection(game, sockaddr);
		return ;
	}

	t_client 	*client;

	client = srvGetClient(game->server, cp->clientID);
	if (client)
	{
		if (memcmp(&(client->sockaddr), sockaddr, sizeof(SOCKADDR_IN)) != 0)
		{
			packet_handler[cp->packet.header.id](game, cp, client);
		}
		else
		{
			logger_log(LOG_WARNING, "Received a packet from a valid clientID but from wrong adress! hacking?");
		}
	}
	else
	{
		logger_log(LOG_WARNING, "Received a packet from an unknown client!");
	}
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