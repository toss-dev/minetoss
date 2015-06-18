/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 12:31:05 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/07 18:37:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	rand_float_in_range(float min, float max)
{
	float f;
	float value;

	f = rand() / (float)RAND_MAX;
	value = f * (max - min) + min;
	return (value);
}

int 	rand_in_range(int min, int max)
{
	return (rand() % (max - min) + min);
}

int 	rand_int(int max)
{
	return (rand() % max);
}
