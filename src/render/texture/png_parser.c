/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:38:46 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/07 15:37:26 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	loadPngFile(char const *file, t_texture *texture)
{
	unsigned	error;
	
	texture->internalformat = GL_RGBA;
	texture->format = GL_RGBA;
	error = lodepng_decode32_file(&(texture->pixels),
									&(texture->width),
									&(texture->height),
									file);
	if (error)
	{
		logger_log(LOG_ERROR, "Error while loading png file %u: %s : %s", error, lodepng_error_text(error), file);
		return (-1);
	}
	return (1);
}
