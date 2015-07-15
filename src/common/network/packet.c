#include "common/common.h"

void 	packetCreate(t_packet *packet, BYTE *data, unsigned int size, unsigned short id)
{
	size = MIN(size, PACKET_MAX_SIZE);
	packet->header.id = id;
	packet->header.size = size;
	memcpy(packet->data, data, size);
}

void	packetDelete(t_packet *packet)
{
	memset(packet, 0, sizeof(t_packet));
}

/** return the number of read octets, -1 on read error, -2 on tiemout */
int		packetReceive(t_packet *packet, SOCKET sock, SOCKADDR_IN *sockaddr, unsigned int sec, unsigned int usec)
{
	struct timeval	tv;
	fd_set 			rdfs;

   	tv.tv_sec = sec;
   	tv.tv_usec = usec;
  	FD_ZERO(&rdfs);
   	FD_SET(sock, &rdfs);

	if (select(sock + 1, &rdfs, NULL, NULL, &tv) == -1)
	{
		perror("select()");
		return (PACKET_SELECT_ERROR);
	}

	if (FD_ISSET(sock, &rdfs))
	{
		return (packetRead(packet, sock, sockaddr));
	}
	return (PACKET_TIMEOUT);
}

/**
**	return the number of octet writen, or -1 on error
*/
int		packetSend(t_packet *packet, SOCKET sock, SOCKADDR_IN *sockaddr)
{
	int n;

	if ((n = sendto(sock, packet, sizeof(t_packet_header) + packet->header.size, 0, (SOCKADDR*)sockaddr, sizeof(SOCKADDR_IN))) < 0)
	{
		perror("send()");
		return (-1);
	}
	logger_log(LOG_FINE, "Sent: size: %d ; id: %d", packet->header.size, packet->header.id);
	return (n);
}

/**
**	return -1 on error, or the size of the packet (in octets)
*/
int 	packetRead(t_packet *packet, SOCKET sock, SOCKADDR_IN *sockaddr)
{
   int         n;
   socklen_t   sockaddrsize = sizeof(SOCKADDR_IN);

   if ((n = recvfrom(sock, packet, sizeof(packet), 0, (SOCKADDR*)sockaddr, &sockaddrsize)) < 0)
   {
      perror("recvfrom()");
      return (-1);
   }
   logger_log(LOG_FINE, "Received: size: %d ; id: %d", packet->header.size, packet->header.id);
   return (n);
}
