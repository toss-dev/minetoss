/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/main.h"

static void srvPacketHandler(t_server *server, t_packet *packet, SOCKADDR_IN *csin)
{
   (void)server;
   (void)csin;
   printf("SERVER: packet received: size: %d id: %d\n", packet->header.size, packet->header.id);
   packetSend(server->sock, csin, packet);
}

int		main(void)
{
	t_server   *server;

	server = srvStart(4242, MAX_SERVER_CLIENT);
	srvLoop(server, srvPacketHandler);
	srvStop(server);
	return (0);
}
