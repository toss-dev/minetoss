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

   return (server);
}

void  srvStop(t_server *server)
{
	# ifdef WIN32
		WSACleanup();
	# endif
   close(server->sock);
   free(server);
}

int   srvAddClient(t_server *server, SOCKADDR_IN *sockaddr)
{
   if (server->client_count >= SRV_MAX_CLIENT)
   {
      return (0);
   }
   memcpy(&(server->clients[server->client_count].sockaddr), sockaddr, sizeof(SOCKADDR_IN));
   server->client_count = server->client_count + 1;
   return (1);
}

/**
** read one packet, store it into "packet", store client socket address in "sockaddr"
*/
int   srvPacketRead(t_server *server, t_client_packet *cp, SOCKADDR_IN *sockaddr)
{
   int         n;
   socklen_t   sockaddrsize = sizeof(SOCKADDR_IN);

   if ((n = recvfrom(server->sock, cp, sizeof(t_client_packet), 0, (SOCKADDR*)sockaddr, &sockaddrsize)) < 0)
   {
      perror("recvfrom()");
      return (-1);
   }
   logger_log(LOG_FINE, "Server received: size: %d ; id: %d", cp->packet.header.size, cp->packet.header.id);
   return (n);
}

t_client *srvGetClient(t_server *server, int clientID)
{
   if (clientID < 0 || clientID >= SRV_MAX_CLIENT)
   {
      return (NULL);
   }
   return (server->clients + clientID);
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