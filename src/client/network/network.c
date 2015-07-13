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

//thread network main function
static void	networkStartLoop(t_game *game)
{
	t_function	packet_handler[PACKET_ID_MAX] = {
		packetHandlerConnection
	};
	t_packet 	*packet;

	while (isGameRunning(game))
	{
		while ((packet = cltGetNextPacket(game->client)) != NULL)
		{
			packet_handler[packet->header.id](game, packet);
			cltPopPacket(game->client);
		}
		usleep(1000);
	}
	pthread_exit(EXIT_SUCCESS);
}

void	startNetwork(t_game *game)
{
	game->client = cltStart("localhost", 4242);
	if (game->client == NULL)
	{
		logger_log(LOG_ERROR, "Couldnt connect to host.");
		exit(EXIT_FAILURE);
	}

	//create the thread that will pop packets from the queue and handle it
	if (pthread_create(game->threads + THRD_NETWORK, NULL, (t_pthread_start)networkStartLoop, game) != 0)
	{
		logger_log(LOG_ERROR, "Couldnt start network thread");
		exit(EXIT_FAILURE);
	}
}

void	stopNetwork(t_game *game)
{
	cltStop(game->client);
	game->client = NULL;
}