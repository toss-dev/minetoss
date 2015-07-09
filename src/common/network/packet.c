#include "common/common.h"

void 	packetCreate(t_packet *packet, BYTE *data, short size, BYTE id)
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
	return (n);
}

/**
**	return -1 on error, or the size of the packet (in octets)
*/
int 	packetRead(SOCKET sock, SOCKADDR_IN *sin, t_packet *packet)
{
   int         n;
   socklen_t   sinsize = sizeof(SOCKADDR_IN);

   if ((n = recvfrom(sock, packet, sizeof(packet), 0, (SOCKADDR*)sin, &sinsize)) < 0)
   {
      perror("recvfrom()");
      return (-1);
   }
   return (n);
}
