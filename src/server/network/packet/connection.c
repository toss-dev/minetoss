/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/main.h"

void	packetHandlerConnection(t_game *game, SOCKADDR_IN *sockaddr)
{
	t_packet    packet;
	int         response;

	if (srvAddClient(game->server, sockaddr))
	{
		response = game->server->client_count - 1;
	}
	else
	{
		response = WRONG_CLIENT_ID;
	}
   packetCreate(&packet, (BYTE*)&response, sizeof(int), PACKET_ID_CONNECTION);
   packetSend(&packet, game->server->sock, sockaddr);
}