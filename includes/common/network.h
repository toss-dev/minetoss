/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 00:05:11 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/03 00:06:01 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_H
# define NETWORK_H

# include "libft.h"

# define SESSION_ID_SIZE 16
# define WRONG_CLIENT_ID -1


/** threads */
typedef void	*(*t_pthread_start)(void *);

enum e_packet_id
{
	PACKET_ID_CONNECTION,
	PACKET_ID_MAX
};

typedef unsigned char	BYTE;
typedef unsigned int 	PORT;
typedef struct protoent	PROTOENT;

# define PACKET_MAX_SIZE	1024
# define PACKET_MAGIC		42

# ifdef WIN32
#	include <winsock2.h> 
# else
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <unistd.h> /* close */
#	include <netdb.h> /* gethostbyname */
#	define INVALID_SOCKET -1
#	define SOCKET_ERROR -1
#	define closesocket(s) close(s)

	typedef int 				SOCKET;
	typedef struct sockaddr_in 	SOCKADDR_IN;
	typedef struct sockaddr 	SOCKADDR;
	typedef struct in_addr		IN_ADDR;
	typedef struct hostent		HOSTENT;
# endif

typedef struct 	s_packet_header
{
	unsigned short	id;
	unsigned short	size;
}				t_packet_header;

typedef struct 	s_packet
{
	t_packet_header	header;
	BYTE			data[PACKET_MAX_SIZE];
}				t_packet;

typedef struct 	s_client_packet
{
	int 		clientID;
	t_packet 	packet;
}				t_client_packet;

void	packetDelete(t_packet *packet);
void 	packetCreate(t_packet *packet, BYTE *data, short size, short id);
int		packetSend(t_packet *packet, SOCKET sock, SOCKADDR_IN *sockaddr);
int 	packetRead(t_packet *packet, SOCKET sock, SOCKADDR_IN *sockaddr);
int		packetReceive(t_packet *packet, SOCKET sock, SOCKADDR_IN *sin, unsigned int sec, unsigned int usec);

#endif