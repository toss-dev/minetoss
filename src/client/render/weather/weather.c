/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weather.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 15:45:55 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/07 15:46:15 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

void 	loadWeather(t_weather *weather)
{
	weather->sun_pos = new_vec3(0, TERRAIN_SIZEY, 0);
	weather->sun_color = new_vec3(1, 1, 1);
	weather->fog_color = new_vec3(0.8f, 0.8f, 0.8f);
	weather->fog_density = 0.005f;
	weather->fog_gradient = 2.5f;
}

void	updateWeather(t_world *world, t_renderer *renderer, t_timer *timer)
{
	updateSky(world, renderer, timer);
}
