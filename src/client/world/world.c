/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 23:14:27 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/02 23:21:49 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

void	initWorld(t_world *world)
{
	world->terrains = htab_new(CHUNK_HASHTABLE_SIZE);
	world->terrain_garbage = array_list_new(128, sizeof(t_point3));

	logger_log(LOG_FINE, "Loading world terrains");
	loadTerrains(world);
	
	logger_log(LOG_FINE, "Loading world weather");
	loadWeather(&(world->weather));
}

/******************************************************************************/
/**                      UPDATE RELATED FUNCTIONS:                            */
/******************************************************************************/

void	updateWorld(t_world *world)
{
	updateTerrains(world);
}

/******************************************************************************/
