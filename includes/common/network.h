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

# define PROTOCOL_EXPERIMENTAL 253 //RFC protocol id for experimental protocols

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

	typedef int SOCKET;
	typedef struct sockaddr_in 	SOCKADDR_IN;
	typedef struct sockaddr 	SOCKADDR;
	typedef struct in_addr		IN_ADDR;
	typedef struct hostent		HOSTENT;
# endif

typedef char	t_session_id[16];

typedef struct 	s_packet_header
{
	short			id;
	short			size;
	t_session_id	sessionID;
}				t_packet_header;

typedef struct 	s_packet
{
	t_packet_header	header;
	BYTE			data[PACKET_MAX_SIZE];
}				t_packet;

void	packetDelete(t_packet *packet);
void 	packetCreate(t_packet *packet, BYTE *data, short size, short id, t_session_id sessionID);
int		packetSend(SOCKET sock, SOCKADDR_IN *sin, t_packet *packet);
int 	packetRead(SOCKET sock, SOCKADDR_IN *sin, t_packet *packet);
int		packetReceive(SOCKET sock, SOCKADDR_IN *sin, unsigned int sec, unsigned int usec, t_packet *packet);

typedef void   (*t_packet_handler)(void *extra, BYTE data[PACKET_MAX_SIZE], unsigned int size, unsigned int id);



#endif