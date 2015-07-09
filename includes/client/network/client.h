/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H

# define CLIENT_H

# include "common/network.h"

typedef struct 	s_client
{
	unsigned int	id;
	SOCKET			sock;
	SOCKADDR_IN		sin;
	char			*hostname;
	PORT			port;
	unsigned		state;
}				t_client;

enum e_client_state
{
	CLIENT_CONNECTED = 1
};

t_client	*cltConnect(char const *hostname, PORT port);
void		cltDisconnect(t_client *client);

#endif