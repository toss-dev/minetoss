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

static void cltLoop(t_client *client)
{
   t_packet    packet;

   while (client->state & CLIENT_RUNNING)
   {
      if (packetReceive(&packet, client->sock, &(client->sockaddr), 0, 10000) > 0)
      {
         if (packet.header.id >= PACKET_ID_MAX)
         {
            logger_log(LOG_WARNING, "Received an unknown packet!");
            continue ;
         }

         if (packet.header.size >= PACKET_MAX_SIZE)
         {
            logger_log(LOG_WARNING, "Received a too big packet!");
            continue ;
         }

         list_add(&(client->packet_queue), &(packet), sizeof(t_packet_header) + packet.header.size);
      }
   }
}


static void cltInit(void)
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
}

static t_client   *cltNew(char const *hostname, PORT port)
{
   t_client    *client;

   client = (t_client*)malloc(sizeof(t_client));
   if (client == NULL)
   {
      perror("malloc");
      exit(EXIT_FAILURE);
   }

   client->port = port;
   client->hostname = strdup(hostname);
   client->state = 0;
   client->clientID = -1;
   client->packet_queue = list_new();

   client->ticks = 0;
   client->last_live = time(NULL);

   return (client);
}

static void cltStartSocket(t_client *client)
{
   HOSTENT  *hostinfo;

   client->sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

   if (client->sock == INVALID_SOCKET)
   {
      perror("socket()");
      free(client->hostname);
      free(client);
      exit(EXIT_FAILURE);
   }

   hostinfo = gethostbyname(client->hostname);
   if (hostinfo == NULL)
   {
      fprintf(stderr, "Unknown host %s.\n", client->hostname);
      free(client->hostname);
      free(client);
      exit(EXIT_FAILURE);
   }

   client->sockaddr.sin_addr = *((IN_ADDR*)hostinfo->h_addr);
   client->sockaddr.sin_port = htons(client->port);
   client->sockaddr.sin_family = AF_INET;
}

static void cltConnect(t_client *client)
{
   t_client_packet packet;

   cltPacketCreate(client, &packet, NULL, 0, PACKET_ID_CONNECTION);
   cltPacketSend(client, &packet);


   t_packet response;

   if (packetReceive(&response, client->sock, &(client->sockaddr), CONNEXION_TIMEOUT, 0) < 0)
   {
      logger_log(LOG_ERROR, "Couldn't connect to server! ;)");
   }
   else
   {
      packetHandlerConnection(client, &(response));
   }
}

t_client *cltStart(char const *hostname, PORT port)
{
   t_client       *client;

   cltInit();
   client = cltNew(hostname, port);
   cltStartSocket(client);

   client->state = client->state | CLIENT_RUNNING;

   if (pthread_create(&(client->packet_queue_thread), NULL, (t_pthread_start)cltLoop, client) != 0)
   {
      logger_log(LOG_ERROR, "Couldnt start client thread");
      exit(EXIT_FAILURE);
   }

   cltConnect(client);

   return (client);
}

void	cltStop(t_client *client)
{
   client->state = client->state & ~(CLIENT_RUNNING);
   client->state = client->state & ~(CLIENT_CONNECTED);

   pthread_join(client->packet_queue_thread, NULL);

	# ifdef WIN32
	   WSACleanup();
	# endif
	closesocket(client->sock);
	free(client->hostname);
	client->hostname = NULL;
}

/** tick the client once:
**
** send to the server that the client is still connected
*/
void     cltTick(t_client *client)
{
   if (client->last_live - time(NULL) >= LIVE_TIMEOUT)
   {
      logger_log(LOG_ERROR, "The server didnt send live packet for %d ticks\n", client->ticks - client->last_live);
   }
   ++client->ticks;
}

/** send to the server that the client is alive */
void     cltLive(t_client *client)
{
   t_client_packet   packet;

   client->last_live = client->ticks;
   cltPacketCreate(client, &packet, NULL, 0, PACKET_ID_LIVE);
   cltPacketSend(client, &packet);
}

/** return the first packet */
t_packet    *cltGetNextPacket(t_client *client)
{
   return (list_head(&(client->packet_queue)));
}

/** delete the first packet */
void        cltPopPacket(t_client *client)
{
   list_pop(&(client->packet_queue), NULL);
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