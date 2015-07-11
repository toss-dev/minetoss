/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H

# define CLIENT_H

# include "common/network.h"

typedef struct 	s_client
{
	BYTE 			sessionID[SESSION_ID_SIZE];
	SOCKET			sock;
	SOCKADDR_IN		sockaddr;
	char			*hostname;
	PORT			port;
	unsigned		state;
}				t_client;

enum e_client_state
{
	CLIENT_CONNECTED = 1
};

t_client	*cltInit(char const *hostname, PORT port);
void		cltStop(t_client *client);

void 		cltPacketCreate(t_client *client, t_client_packet *cp, BYTE *data, short size, short id);
int 		cltPacketSend(t_client *client, t_client_packet *cp);

#endif