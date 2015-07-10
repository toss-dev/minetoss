#include "common/common.h"

void 	packetCreate(t_packet *packet, BYTE *data, short size, short id, t_session_id sessionID)
{
	size = MIN(size, PACKET_MAX_SIZE);
	packet->header.id = id;
	packet->header.size = size;
	memcpy(packet->header.sessionID, sessionID, sizeof(t_session_id));
	memcpy(packet->data, data, size);
}

void	packetDelete(t_packet *packet)
{
	memset(packet, 0, sizeof(t_packet));
}

/** return the number of read octets, -1 on read error, -2 on tiemout */
int		packetReceive(SOCKET sock, SOCKADDR_IN *sin, unsigned int sec, unsigned int usec, t_packet *packet)
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
		return (-1);
	}

	if (FD_ISSET(sock, &rdfs))
	{
		return (packetRead(sock, sin, packet));
	}
	return (-2);
}

/**
**	return the number of octet writen, or -1 on error
*/
int		packetSend(SOCKET sock, SOCKADDR_IN *sin, t_packet *packet)
{
	int n;

	if ((n = sendto(sock, packet, sizeof(t_packet_header) + packet->header.size, 0, (SOCKADDR*)sin, sizeof(SOCKADDR_IN))) < 0)
	{
		perror("send()");
		return (-1);
	}
	printf("%d\n", n);
	return (n);
}

/**
**	return -1 on error, or the size of the packet (in octets)
*/
int 	packetRead(SOCKET sock, SOCKADDR_IN *sin, t_packet *packet)
{
   int         n;
   socklen_t   sinsize = sizeof(SOCKADDR_IN);

   puts("i read");
   if ((n = recvfrom(sock, packet, sizeof(packet), 0, (SOCKADDR*)sin, &sinsize)) < 0)
   {
      perror("recvfrom()");
      return (-1);
   }
   puts("i stop");
   return (n);
}
