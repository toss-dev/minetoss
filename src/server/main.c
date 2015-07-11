/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/main.h"

/**

	The client has to send a certain packet asking for it token

	the server generate, save, and send the token to the client

	the token is 16 octets long

	everytime the client send a message to the server, the token is send with it

	the server get the client from it token, and handle the packet

	if the token is invalid, the server say to the client that he is not connected

	if the server receive an invalid / unexisting token, it ignore it

**/

int		main(void)
{
	t_game	*game;

	game = (t_game*)malloc(sizeof(t_game));
	if (game == NULL)
	{
		logger_log(LOG_ERROR, "Not enough memory!");
		exit(EXIT_FAILURE);
	}
	gameInit(game);
	gameStart(game);
	gameLoop(game);
	gameStop(game);

	return (0);
}
