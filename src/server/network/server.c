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

int        srvClientHasState(t_client *client, unsigned int state)
{
   return (client->state & state);
}

void        srvClientSetState(t_client *client, unsigned int state)
{
    client->state |= state;
}

void        srvClientUnsetState(t_client *client, unsigned int state)
{
   client->state &= ~(state);
}

/** add the client */
static int  srvConnectClient(t_server *server, SOCKADDR_IN *sockaddr)
{
   t_client *client;
   int      clientID;

   if (server->client_count >= SRV_MAX_CLIENT)
   {
      logger_log(LOG_WARNING, "Server is full!");
      return (WRONG_CLIENT_ID);
   }

   for (clientID = 0 ; clientID < SRV_MAX_CLIENT ; clientID++)
   {
      client = server->clients + clientID;

      if (srvClientHasState(client, CLIENT_CONNECTED) == 0)
      {
         memcpy(&(client->sockaddr), sockaddr, sizeof(SOCKADDR_IN));

         logger_log(LOG_FINE, "A client has connected!");

         t_packet packet;

         packetCreate(&packet, (BYTE*)&clientID, sizeof(int), PACKET_ID_CONNECTION);
         packetSend(&packet, server->sock, sockaddr);

         client->last_live_received = time(NULL);
         client->last_live_sent = client->last_live_received ;
         server->client_count = server->client_count + 1;
         srvClientSetState(client, CLIENT_CONNECTED);

         return (clientID);
      }
   }

   logger_log(LOG_WARNING, "Server is full!");
   return (WRONG_CLIENT_ID);
}

/**
** do a server tick:
**
** for every clients:
**    check when the last live ping was received
**    if it was more than LIVE_PING_TIMER seconds ago, the server
**    send a packet to the client, asking it if it is still connected
**    after a LIVE_TIMEOUT seconds timeout, if the client didnt responsed,
**    it is disconnected from the server
*/
void        srvTick(t_server *server)
{
   t_client       *client;
   unsigned int   clientID;
   time_t         now;

   now = time(NULL);
   for (clientID = 0 ; clientID < SRV_MAX_CLIENT ; clientID++)
   {
      client = server->clients + clientID;
      if (srvClientHasState(client, CLIENT_CONNECTED))
      {
         size_t   diff;

         diff = now - client->last_live_received;
         if (diff >= LIVE_TIMEOUT)
         {
            logger_log(LOG_WARNING, "Client with id: %u has been killed! (%u)", clientID, diff);
            srvClientUnsetState(client, CLIENT_CONNECTED);
            server->client_count = server->client_count - 1;
         }
         else if (diff >= LIVE_PING_TIMER && now - client->last_live_sent >= LIVE_PING_TIMER)
         {
            //send the ping live to the client
            t_packet packet;

            packetCreate(&(packet), NULL, 0, PACKET_ID_LIVE);
            srvSendPacket(server, &(packet), client);
            client->last_live_sent = now;
         }
      }
   }
   ++server->ticks;
}

/** tell the server that the given client is alive */
void        srvCltLive(t_client *client)
{
   client->last_live_received = time(NULL);
}

/** independant thread loop that queue packets into the server->packet_queue list */
static void srvQueuePackets(t_server *server)
{
   t_client          *sender;
   t_server_packet   sp;
   SOCKADDR_IN       sockaddr;

   while (server->state & SERVER_RUNNING)
   {
      if (srvPacketReceive(server, &(sp.cp), &(sockaddr), 2, 0) > 0)
      {
         if (sp.cp.packet.header.id >= PACKET_ID_MAX)
         {
            logger_log(LOG_WARNING, "Received an unknown packet id!");
            continue ;
         }

         if (sp.cp.packet.header.size >= PACKET_MAX_SIZE)
         {
            logger_log(LOG_WARNING, "Received a too big packet!");
            continue ;
         }

         sender = srvGetClient(server, sp.cp.clientID);

         if (sender)
         {
            if (memcmp(&(sender->sockaddr), &(sockaddr), sizeof(SOCKADDR_IN)) == 0)
            {
               sp.sender = sender;
               list_add(&(server->packet_queue), &sp, sizeof(t_server_packet));
            }
            else
            {
               logger_log(LOG_WARNING, "Received a packet from a valid clientID but from wrong adress! hacking?");
            }
         }
         else if (sp.cp.packet.header.id == PACKET_ID_CONNECTION)
         {
            srvConnectClient(server, &(sockaddr));
         }
         else
         {
            logger_log(LOG_WARNING, "Received a packet from an unknown client! (%d)" , sp.cp.clientID);
         }
      }
      else  //no packet received during 2 second, server make a pause
      {
         sleep(1);
      }
   }
   pthread_exit(EXIT_SUCCESS);
}

static void srvInit(void)
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
}

static t_server *srvNew(PORT port)
{
   t_server    *server;

   server = (t_server*)malloc(sizeof(t_server));
   if (server == NULL)
   {
      perror("malloc");
      exit(EXIT_FAILURE);
   }

   server->state = 0;
   server->port = port;
   server->packet_queue = list_new();

   return (server);
}

static void srvStartSocket(t_server *server)
{
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
}

/**
**    port: the port on which the server will listen to
**
**    max_client_live: the number of called to srvTick() before a client is
**                 kick if it hasnt sent a live packet
*/
t_server *srvStart(PORT port)
{
   t_server *server;

   srvInit();
   server = srvNew(port);
   srvStartSocket(server);

   server->state = server->state | SERVER_RUNNING;
   server->state = server->state | SERVER_INITIALIZED;
   server->ticks = 0;
   memset(server->clients, 0, sizeof(server->clients));

   if (pthread_create(&(server->packet_queue_thread), NULL, (t_pthread_start)srvQueuePackets, server) != 0)
   {
      logger_log(LOG_ERROR, "Couldnt start network handler thread");
      exit(EXIT_FAILURE);
   }
   return (server);
}

void  srvStop(t_server *server)
{
   server->state = server->state & ~(SERVER_INITIALIZED);
   server->state = server->state & ~(SERVER_RUNNING);

   pthread_join(server->packet_queue_thread, NULL);

	# ifdef WIN32
		WSACleanup();
	# endif
   close(server->sock);
   list_delete(&(server->packet_queue), NULL);
   free(server);
}

/** return the first packet */
t_server_packet   *srvGetNextPacket(t_server *server)
{
   return (list_head(&(server->packet_queue)));
}

/** delete the first packet */
void  srvPopPacket(t_server *server)
{
   list_pop(&(server->packet_queue), NULL);
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

/** send the given packet to the given client */
void  srvSendPacket(t_server *server, t_packet *packet, t_client *client)
{
   packetSend(packet, server->sock, &(client->sockaddr));
}