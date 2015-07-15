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

# define CONNEXION_TIMEOUT 5 	//in seconds

# include "common/network.h"

typedef struct 	s_client
{
	int 			clientID;	//clientID send by the server
	SOCKET			sock;		//server socket
	SOCKADDR_IN		sockaddr;	//server addr
	char			*hostname;	//server hostname
	PORT			port;		//server port in which it is listening
	unsigned		state;		//client state (see enum below)
	t_list 			packet_queue;	//a queue in which every received packet are put to
	pthread_t		packet_queue_thread; //the thread which queue packets
	time_t			last_live;
	unsigned int	ticks;		//number of tick executed
}				t_client;

enum e_client_state
{
	CLIENT_CONNECTED = 1,
	CLIENT_RUNNING = 2,
};

t_client	*cltStart(char const *hostname, PORT port);
void		cltStop(t_client *client);

void 		cltPacketCreate(t_client *client, t_client_packet *cp, BYTE *data, short size, short id);
int 		cltPacketSend(t_client *client, t_client_packet *cp);

t_packet 	*cltGetNextPacket(t_client *client);
void 		cltPopPacket(t_client *client);

void 		cltTick(t_client *client);
void     	cltLive(t_client *client);

/** packet handler */
void		packetHandlerConnection(t_client *client, t_packet *packet);

#endif