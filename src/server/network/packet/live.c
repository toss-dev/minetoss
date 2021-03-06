/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 19:51:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 15:13:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/main.h"

/**
**
**	The server send to every client every 15 seconds that it is alive
**
**	each client has to answer that they are also alive, elseway, after another
**  15 seconds timeout, the client is disconnected
**
*/

/** called whenever the server received a live packet */
void 	packetHandlerLive(t_game *game, t_server_packet *sp)
{
	srvCltLive(sp->sender);
	(void)game;
}
