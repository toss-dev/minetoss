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

t_server *srvStart(PORT port, unsigned int max_client)
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

   server->clients = (t_client*)malloc(sizeof(t_client) * max_client);
   if (server->clients == NULL)
   {
      perror("malloc");
      exit(EXIT_FAILURE);
   }
   memset(server->clients, 0, sizeof(t_client) * max_client);

   server->max_client = max_client;
   server->client_count = 0;
   server->port = port;

   server->sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if (server->sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   server->sin.sin_addr.s_addr   = htonl(INADDR_ANY);
   server->sin.sin_port          = htons(server->port);
   server->sin.sin_family        = AF_INET;

   if (bind(server->sock,(SOCKADDR*)&(server->sin), sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
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
   closesocket(server->sock);
   free(server->clients);
   free(server);
}

t_client *srvGetClient(t_server *server, SOCKADDR_IN *csin)
{
   (void)csin;
   return (server->clients + 0);
}

void  srvLoop(t_server *server, t_function packet_handler)
{
   fd_set      rdfs;

   while (1)
   {
      FD_ZERO(&rdfs);
      FD_SET(STDIN_FILENO, &rdfs);
      FD_SET(server->sock, &rdfs);

      if (select(server->sock + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

      if (FD_ISSET(STDIN_FILENO, &rdfs)) /** stop the server if something enter stdin */
      {
         break;
      }
      else if (FD_ISSET(server->sock, &rdfs))
      {
         SOCKADDR_IN csin;
         t_packet    packet;

         if (packetRead(server->sock, &csin, &packet) >= 0)
         {
            packet_handler(server, packet, &csin);
         }
      }
   }
}
