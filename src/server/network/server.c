/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/network/server.h"


/* sessionID generator starts here */

unsigned int   session_token;

static unsigned int srvHashInt(unsigned int x)
{
   x = ((x >> 16) ^ x) * 0x45d9f3b;
   x = ((x >> 16) ^ x) * 0x45d9f3b;
   x = ((x >> 16) ^ x);
   return (x);
}

void  srvNewSessionID(BYTE sessionID[SESSION_ID_SIZE])
{
   memcpy(sessionID + 0, &session_token, 4);
   session_token = srvHashInt(session_token);
   memcpy(sessionID + 4, &session_token, 4);
   session_token = srvHashInt(session_token);
   memcpy(sessionID + 8, &session_token, 4);
   session_token = srvHashInt(session_token);
   memcpy(sessionID + 12, &session_token, 4);
   session_token = srvHashInt(session_token);
   sessionID[SESSION_ID_SIZE - 1] = 0;
}

/** sessionID generator ends here */

t_server *srvStart(PORT port)
{
   # ifdef WIN32
      WSADATA wsa;
      int err = WSAStartup(MAKEWORD(2, 2), &wsa);
      if (err < 0)
      {
         puts("WSAStartup failed !");
         exit(EXIT_FAILURE);
      }
   # endif

   t_server *server;

   server = (t_server*)malloc(sizeof(t_server));
   if (server == NULL)
   {
      perror("malloc");
      exit(EXIT_FAILURE);
   }
   memset(server, 0, sizeof(t_server));

   server->clients = htab_new(8192);
   server->client_count = 0;
   server->port = port;

   server->sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if (server->sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   server->sockaddr.sin_addr.s_addr   = htonl(INADDR_ANY);
   server->sockaddr.sin_port          = htons(server->port);
   server->sockaddr.sin_family        = AF_INET;

   if (bind(server->sock,(SOCKADDR*)&(server->sockaddr), sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
   {
      perror("bind()");
      exit(errno);
   }

   server->state = server->state | SERVER_INITIALIZED;
   session_token = srvHashInt(time(NULL));
   return (server);
}

static void srvClientDelete(t_client *client)
{
   (void)client;
}

void  srvStop(t_server *server)
{
	# ifdef WIN32
		WSACleanup();
	# endif
   closesocket(server->sock);
   htab_delete(&(server->clients), srvClientDelete);
   free(server);
}

void  srvAddClient(t_server *server, SOCKADDR_IN *sockaddr)
{
   t_packet packet;
   t_client client;

   if (server->client_count >= 1024)
   {
      //server is full, say the client the server is full
   }
   else
   {
      srvNewSessionID(client.sessionID);
      memcpy(&(client.sockaddr), sockaddr, sizeof(SOCKADDR_IN));
      htab_insert(server->clients, (char*)client.sessionID, &client, sizeof(t_client)); 
      server->client_count++;
      packetCreate(&packet, client.sessionID, sizeof(client.sessionID), PACKET_ID_CONNECTION);
   }
}

/**
** read one packet, store it into "packet", store client socket address in "sockaddr", and it sessionID into "sessionID"
*/
int   srvPacketRead(t_server *server, t_client_packet *packet, SOCKADDR_IN *sockaddr)
{
   int         n;
   socklen_t   sockaddrsize = sizeof(SOCKADDR_IN);

   if ((n = recvfrom(server->sock, packet, sizeof(t_client_packet), 0, (SOCKADDR*)sockaddr, &sockaddrsize)) < 0)
   {
      perror("recvfrom()");
      return (-1);
   }
   return (n);
}

/** return the number of read octets, -1 on read error, -2 on timeout */
int      srvPacketReceive(t_server *server, t_client_packet *packet, SOCKADDR_IN *sockaddr, unsigned int sec, unsigned int usec)
{
   struct timeval tv;
   fd_set         rdfs;

   tv.tv_sec = sec;
   tv.tv_usec = usec;
   FD_ZERO(&rdfs);
   FD_SET(server->sock, &rdfs);

   if (select(server->sock + 1, &rdfs, NULL, NULL, &tv) == -1)
   {
      perror("select()");
      return (-1);
   }

   if (FD_ISSET(server->sock, &rdfs))
   {
      return (srvPacketRead(server, packet, sockaddr));
   }
   return (-2);
}