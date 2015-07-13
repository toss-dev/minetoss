/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 00:05:11 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/03 00:06:01 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** HOW SERVER WORKS? IT IS EASY MOTHER FUCKERS! */

/**
**
**	The server starts when the function 'srvStart()' is called.
**	Once it is started, the server created a thread that will read packet on it socket
**
**	When a packet is read, it get the sending 't_client'
**	If the client couldnt be found:
**		if the client sent the connection packet, the server try to connect it
**		else, the client is trying to send bad data to the server: the server ignore it
**	else if the client is found, the packet is added to the packet queue
**
**	to get a packet from the queue, use 'srvGetNextPacket()'
**	to remove the packet (you may want to whenever the packet is handled), call 'srvPopPacket()'
*/

#ifndef SERVER_H

# define SERVER_H

# include "common/network.h"
# include <pthread.h>

# define SRV_MAX_CLIENT 1024
# define SERVER_QUEUE_SIZE 64

enum 	e_server_state
{
	SERVER_INITIALIZED = 1,
	SERVER_RUNNING = 2
};

enum 	e_client_state
{
	CLIENT_CONNECTED = 1
};

typedef struct 	s_client
{
	unsigned int 	state;
	SOCKADDR_IN		sockaddr;
}				t_client;

typedef struct 	s_server_packet
{
	t_client		*sender;
	t_client_packet	cp;
}				t_server_packet;

typedef struct 	s_server
{
	t_client		clients[SRV_MAX_CLIENT];
	unsigned int 	client_count;
	PORT 			port;
	SOCKET 			sock;
	SOCKADDR_IN		sockaddr;
	unsigned		state;
	pthread_t		packet_queue_thread;
	t_list			packet_queue;
}				t_server;

t_server			*srvStart(PORT port);
void				srvStop(t_server *server);
t_client 			*srvGetClient(t_server *server, int id);

int      			srvPacketReceive(t_server *server, t_client_packet *packet, SOCKADDR_IN *sockaddr,
								unsigned int sec, unsigned int usec);

void              	srvPopPacket(t_server *server);
t_server_packet   	*srvGetNextPacket(t_server *server);

int        			srvClientHasState(t_server *server, unsigned int clientID, unsigned int state);
void       			srvClientSetState(t_server *server, unsigned int clientID, unsigned int state);
void        		srvClientUnsetState(t_server *server, unsigned int clientID, unsigned int state);

#endif