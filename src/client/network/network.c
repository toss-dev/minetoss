/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 19:51:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 15:13:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

//call when the given packet is received
static void	networkPacketHandler(t_game *game, t_packet *packet, SOCKADDR_IN *sockaddr)
{
	static t_function	packet_handler[PACKET_ID_MAX] = {
		packetHandlerConnection
	};

	if (packet->header.id >= PACKET_ID_MAX)
	{
		logger_log(LOG_WARNING, "Received an unknown packet!");
		return ;
	}

	if (memcmp(&(game->client->sockaddr), sockaddr, sizeof(SOCKADDR_IN)) != 0)
	{
		logger_log(LOG_WARNING, "Received a packet from a wrong server!");
		return ;
	}

	packet_handler[packet->header.id](game, packet);
}

//thread network main function
static void	networkStartLoop(t_game *game)
{
	t_packet 	packet;
	SOCKADDR_IN	sockaddr;
	
	while (isGameRunning(game))
	{
		if (packetReceive(&packet, game->client->sock, &sockaddr, 1, 0) > 0)
		{
			networkPacketHandler(game, &packet, &sockaddr);
		
			t_client_packet	cp;

			cltPacketCreate(game->client, &cp, (BYTE*)"hello", strlen("hello") + 1, PACKET_ID_LOL_STUFF);
			cltPacketSend(game->client, &cp);
		}
	}
	pthread_exit(EXIT_SUCCESS);
}

static void	 connectToServer(t_client *client)
{
	t_client_packet	cp;

	cltPacketCreate(client, &cp, NULL, 0, PACKET_ID_CONNECTION);
	cltPacketSend(client, &cp);
}

void	startNetwork(t_game *game)
{
	connectToServer(game->client);
	if (pthread_create(game->threads + THRD_NETWORK, NULL, (t_pthread_start)networkStartLoop, game) != 0)
	{
		logger_log(LOG_ERROR, "Couldnt start network thread");
		exit(EXIT_FAILURE);
	}
}

void	initNetwork(t_game *game)
{
	game->client = cltInit("localhost", 4242);
	if (game->client == NULL)
	{
		logger_log(LOG_ERROR, "Couldnt connect to host.");
		exit(EXIT_FAILURE);
	}
}

void	stopNetwork(t_game *game)
{
	cltStop(game->client);
	game->client = NULL;
}