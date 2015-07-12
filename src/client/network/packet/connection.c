/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 19:51:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 15:13:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

void	packetHandlerConnection(t_game *game, t_packet *packet)
{
	game->client->clientID = *((int*)packet->data);
	if (game->client->clientID == WRONG_CLIENT_ID)
	{
		logger_log(LOG_ERROR, "Couldnt connect to server, try later maybe!");
	}
	else
	{
		logger_log(LOG_FINE, "You are now connected, your id is: %d", game->client->clientID);
	}
}