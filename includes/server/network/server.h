#ifndef SERVER_H

# define SERVER_H

# include "common/network.h"

# define SERVER_QUEUE_SIZE 64

enum 	e_server_state
{
	SERVER_INITIALIZED = 1,
	SERVER_RUNNING = 2
};

typedef struct 	s_client
{
	BYTE		sessionID[SESSION_ID_SIZE];
	SOCKADDR_IN	sockaddr;
}				t_client;

typedef struct 	s_server
{
	t_htab			clients;
	unsigned int 	client_count;
	PORT 			port;
	SOCKET 			sock;
	SOCKADDR_IN		sockaddr;
	unsigned		state;
}				t_server;

t_server	*srvStart(PORT port);
void		srvStop(t_server *server);
t_client	*srvGetClient(t_server *server, SOCKADDR_IN *sockaddr);

void 		srvNewSessionID(BYTE sessionID[SESSION_ID_SIZE]);

int      	srvPacketReceive(t_server *server, t_client_packet *packet, SOCKADDR_IN *sockaddr,
								unsigned int sec, unsigned int usec);

#endif