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

static void 	packetHandlerDoLolStuff(t_game *game, t_server_packet *sp)
{
	(void)game;
	(void)sp;
	printf("Received a do lol stuff from: %d\n", sp->cp.clientID);
}

/** thread that handle packets */
void	networkHandlePackets(t_game *game)
{
	t_function	packet_handler[PACKET_ID_MAX] = {
		NULL,
		packetHandlerDoLolStuff
	};
	t_server_packet	*sp;

	while (isGameRunning(game))
	{
		while ((sp = srvGetNextPacket(game->server)) != NULL)
		{
			packet_handler[sp->cp.packet.header.id](game, sp);
			srvPopPacket(game->server);
		}
		usleep(1000);
	}
}

/** one thread is created here and will loop reading packets, the other one exit the function */
void	networkStart(t_game *game)
{
	game->server = srvStart(4242);

	if (pthread_create(game->threads + THRD_NETWORK, NULL, (t_pthread_start)networkHandlePackets, game) != 0)
	{
		logger_log(LOG_ERROR, "Couldnt start network handler thread");
		exit(EXIT_FAILURE);
	}
}

void 	networkStop(t_game *game)
{
	srvStop(game->server);
}