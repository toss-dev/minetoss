/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

# ifdef __APPLE__
# 	include <OpenAL/al.h>
# 	include <OpenAL/alc.h>
# else
# 	include <AL/al.h>
# 	include <AL/alc.h>
# endif

# include <unistd.h>
# include <fcntl.h>

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>

typedef struct 	s_wave_file
{
	unsigned int 	size;
	unsigned int 	chunk_size;
	short			format_type;
	short			channels;
	unsigned int	sample_rate;
	unsigned int	avg_bytes_per_sec;
	short			bytes_per_sample;
	short			bits_per_sample;
	unsigned int	data_size;
	unsigned char 	*data;
	unsigned		format;
}				t_wave_file;

typedef struct 	s_sound_manager
{
	ALCcontext		*context;
	ALCdevice		*device;
	ALuint			internal_buffer;
	unsigned int 	sources_count;
	ALuint			*sources;
	unsigned int 	max_files;
	t_wave_file		*files;
}				t_sound_manager;

int  		alhInit(t_sound_manager *manager, unsigned int sources, unsigned int max_files);
void 		alhSetSound(t_sound_manager *manager, char const *file, unsigned soundID);
void		alhStop(t_sound_manager *manager);
void		alhPlaySound(t_sound_manager *manager, unsigned soundID, unsigned sourceID);
int 		alhCheckError(char const *label);
t_wave_file	*alhLoadWaveFile(char const *file);
void 		alhDelete(t_wave_file **file);
void		alhBufferData(ALuint buffer, t_wave_file *file);

#endif