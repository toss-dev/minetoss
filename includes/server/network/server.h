#ifndef SERVER_H

# define SERVER_H

# include "common/network.h"

# define MAX_SERVER_CLIENT 1024
# define SERVER_QUEUE_SIZE 16

enum 	e_server_state
{
	SERVER_INITIALIZED = 1,
	SERVER_RUNNING = 2
};

typedef struct 	s_client
{
	SOCKET		sock;
	SOCKADDR_IN	sin;
}				t_client;

typedef struct 	s_server
{
	t_client		*clients;
	unsigned int	max_client;
	unsigned int 	client_count;
	PORT 			port;
	SOCKET 			sock;
	SOCKADDR_IN		sin;
	unsigned		state;
}				t_server;

t_server	*srvStart(PORT port, unsigned int max_client);
void		srvStop(t_server *server);
t_client	*srvGetClient(t_server *server, SOCKADDR_IN *csin);
void		srvLoop(t_server *server, t_function packet_handler);

#endif