/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skycolor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 23:10:52 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/09 23:11:50 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.h"

# define DEFAULT_SUN_COLOR	new_vec3(1, 1, 1)
# define SUNRISE_COLOR 		new_vec3(2, 1, 0.5f)

t_vec3    mix_color(t_vec3 a, t_vec3 b, float factor)
{
	t_vec3    color;

	color.x = a.x * factor + b.x * (1 - factor);
	color.y = a.y * factor + b.y * (1 - factor);
	color.z = a.z * factor + b.z * (1 - factor);
	return (color);
}

void		calculateSunColor(t_world *world, t_renderer *renderer, float day_ratio)
{
	(void)renderer;
	if (day_ratio >= NIGHT_END && day_ratio < DAY_START / 4)
	{
		world->weather.sun_color = mix_color(DEFAULT_SUN_COLOR, SUNRISE_COLOR, 1 - (day_ratio - NIGHT_END) / (DAY_START / 4));
	}
	else if (day_ratio < DAY_START)
	{
		world->weather.sun_color = mix_color(DEFAULT_SUN_COLOR, SUNRISE_COLOR, (day_ratio - NIGHT_END - DAY_START / 4) / (DAY_START / 4 * 3));
	}
	else
	{
		world->weather.sun_color = DEFAULT_SUN_COLOR;
	}
}
