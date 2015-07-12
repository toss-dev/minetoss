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

t_client *cltInit(char const *hostname, PORT port)
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

   client->sockaddr.sin_addr = *((IN_ADDR*)hostinfo->h_addr);
   client->sockaddr.sin_port = htons(client->port);
   client->sockaddr.sin_family = AF_INET;

   client->clientID = -1;

   return (client);
}

void	cltStop(t_client *client)
{
	# ifdef WIN32
	   WSACleanup();
	# endif
	closesocket(client->sock);
	free(client->hostname);
	client->hostname = NULL;
   client->state = client->state & ~(CLIENT_CONNECTED);
}

void  cltPacketCreate(t_client *client, t_client_packet *cp, BYTE *data, short size, short id)
{
   packetCreate(&(cp->packet), data, size, id);
   cp->clientID = client->clientID;
}

int  cltPacketSend(t_client *client, t_client_packet *cp)
{
   int n;

   //sizeof(header) + sizeof(packet data) + sizeof(client ID)
   if ((n = sendto(client->sock, cp, sizeof(t_packet_header) + cp->packet.header.size + sizeof(int), 0, (SOCKADDR*)&(client->sockaddr), sizeof(SOCKADDR_IN))) < 0)
   {
      perror("send()");
      return (-1);
   }
   logger_log(LOG_FINE, "Client sent: size: %d ; id: %d", cp->packet.header.size, cp->packet.header.id);
   return (n);
}