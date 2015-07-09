/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 19:51:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 15:13:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/network/client.h"

t_client *cltConnect(char const *hostname, PORT port)
{
	# ifdef WIN32
	   WSADATA wsa;
	   int err = WSAStartup(MAKEWORD(2, 2), &wsa);
	   if(err < 0)
	   {
	      puts("WSAStartup failed !");
	      exit(EXIT_FAILURE);
	   }
	# endif


   t_client *client;
   PROTOENT *protocol;
   HOSTENT  *hostinfo;

   client = malloc(sizeof(t_client));
	if (client == NULL)
   {
      perror("malloc");
      exit(EXIT_FAILURE);
   }
   client->port = port;
	client->hostname = strdup(hostname);
	if (client->hostname == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

   protocol = getprotobyname("udp");
   if (protocol == NULL)
   {
      perror("getprotobyname");
      exit(EXIT_FAILURE);
   }
   client->sock = socket(AF_INET, SOCK_DGRAM, protocol->p_proto);
   if (client->sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   hostinfo = gethostbyname(client->hostname);
   if (hostinfo == NULL)
   {
      fprintf(stderr, "Unknown host %s.\n", client->hostname);
      exit(EXIT_FAILURE);
   }

   client->sin.sin_addr = *((IN_ADDR*)hostinfo->h_addr);
   client->sin.sin_port = htons(client->port);
   client->sin.sin_family = AF_INET;

   return (client);
}

void	cltDisconnect(t_client *client)
{
	# ifdef WIN32
	   WSACleanup();
	# endif
	closesocket(client->sock);
	free(client->hostname);
	client->hostname = NULL;
	memset(client, 0, sizeof(t_client));
}

void	cltLoop(t_client *client, t_function packet_handler)
{
   fd_set   rdfs;
   t_packet packet;

   packetCreate(&packet, (BYTE*)"A", 1, 0);
   packetSend(client->sock, &(client->sin), &packet);
   while (1)
   {
      FD_ZERO(&rdfs);
      FD_SET(client->sock, &rdfs);

      if (select(client->sock + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

      if (FD_ISSET(client->sock, &rdfs))
      {
         t_packet packet;
         int      n;

         n = packetRead(client->sock, &(client->sin), &packet);
         if (n == -1)
         {
            printf("Server disconnected !\n");
            break;
         }
         else
         {
            packet_handler(client, packet);
         }
      }
   }
}


/*static void cltPacketHandler(t_client *client, t_packet *packet)
{
   (void)client;
   printf("CLIENT: packet received: size: %d id: %d\n", packet->header.size, packet->header.id);
}


int 	main(void)
{
	t_client   *client;

	client = cltConnect("localhost", 4242);
	cltLoop(client, cltPacketHandler);
	cltDisconnect(client);
	return (0);
}*/