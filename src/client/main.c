/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/23 11:12:52 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/15 15:05:11 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

t_game	*g_game;

int 	main(void)
{
	g_game = gameNew();
	if (g_game == NULL)
	{
		logger_log(LOG_ERROR, "Not enough memory");
		return (EXIT_FAILURE);
	}
	gameLoop(g_game);
	gameStop(g_game);
	gameClean(g_game);
	return (EXIT_SUCCESS);
}
