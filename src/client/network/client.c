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
   HOSTENT  *hostinfo;

   client = (t_client*)malloc(sizeof(t_client));
	if (client == NULL)
   {
      perror("malloc");
      exit(EXIT_FAILURE);
   }
   client->port = port;
	client->hostname = strdup(hostname);
   client->state = 0;
	if (client->hostname == NULL)
	{
		perror("malloc");
      free(client);
      return (NULL);
	}

   client->sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

   if (client->sock == INVALID_SOCKET)
   {
      perror("socket()");
      free(client->hostname);
      free(client);
      return (NULL);
   }

   hostinfo = gethostbyname(client->hostname);
   if (hostinfo == NULL)
   {
      fprintf(stderr, "Unknown host %s.\n", client->hostname);
      free(client->hostname);
      free(client);
      return (NULL);
   }

   client->sin.sin_addr = *((IN_ADDR*)hostinfo->h_addr);
   client->sin.sin_port = htons(client->port);
   client->sin.sin_family = AF_INET;


   t_packet packet;

   packetCreate(&packet, NULL, 0, PACKET_ID_CONNECTION);
   packetSend(client->sock, &(client->sin), &packet);
   if (packetReceive(client->sock, &(client->sin), 5, 0, &packet) < 0)
   {
      logger_log(LOG_ERROR, "Couldnt connect to server, stopping game.");
      exit(EXIT_FAILURE);
   }
   printf("connected, server answered\n");
   client->state = client->state | CLIENT_CONNECTED;
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
   client->state = client->state & ~(CLIENT_CONNECTED);
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