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
static void	networkPacketHandler(t_game *game, t_packet *packet)
{
	(void)game;
	(void)packet;
}

//thread network main function
static void	networkStartLoop(t_game *game)
{
	t_packet    packet;

	while (isGameRunning(game))
	{
		if (packetReceive(game->client->sock, &(game->client->sin), 1, 0, &packet) > 0)
		{
			networkPacketHandler(game, &packet);
		}
	}
	pthread_exit(EXIT_SUCCESS);
}

void	startNetwork(t_game *game)
{
	if (pthread_create(game->threads + THRD_NETWORK, NULL, (t_pthread_start)networkStartLoop, game) != 0)
	{
		logger_log(LOG_ERROR, "Couldnt start network thread");
		exit(EXIT_FAILURE);
	}
}

void	initNetwork(t_game *game)
{
	game->client = cltConnect("localhost", 4242);
	if (game->client == NULL)
	{
		logger_log(LOG_ERROR, "Couldnt connect to host.");
		exit(EXIT_FAILURE);
	}
}

void	stopNetwork(t_game *game)
{
	cltDisconnect(game->client);
	game->client = NULL;
}