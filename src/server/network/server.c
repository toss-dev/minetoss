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

   server->clients = htab_new(8192);
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


