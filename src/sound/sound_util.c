/*****************************************************************************/
/**                           Minetoss game project                          */
/**	                                                         4-----7         */
/**     file:    sound.c                                    /|    /|         */
/**     created: 18 juin 2015 2015 at 22:26:11             0-----3 |         */
/**                                                        | 5___|_6         */
/**                                                        |/    | /         */
/**     by: Romain                                         1-----2	         */
/**                                                                          */
/*****************************************************************************/

#include "sound.h"

void        alhDeleteWaveFile(t_wave_file *file)
{
    free(file->data);
}

t_wave_file *alhLoadWaveFile(char const *filepath)
{
	t_wave_file    *file;
	int 			fd;
    char            buffer[4];

    if ((file = (t_wave_file*)malloc(sizeof(t_wave_file))) == NULL)
    {
        printf("loadWaveFile: not enough memory for file: %s\n", filepath);
        return (NULL);
    }
	if ((fd = open(filepath, O_RDONLY)) == -1)
	{
		printf("loadWaveFile: can't open file %s\n", filepath);
        free(file);
        return (NULL);
	}
	read(fd, buffer, sizeof(buffer));
    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        printf("loadWaveFile: file (%s) no RIFF\n", filepath);
        goto loading_wave_error;
    }
    read(fd, &(file->size), sizeof(unsigned int));
    read(fd, buffer, sizeof(buffer));
    if (strncmp(buffer, "WAVE", 4) != 0)
    {
        printf("loadWaveFile: file (%s) isn't a wave audio file!\n", filepath);
        goto loading_wave_error;
    }
    read(fd, buffer, sizeof(buffer));
    if (strncmp(buffer, "fmt ", 4) != 0)
    {
        printf("loadWaveFile: file (%s) not fmt\n", filepath);
        goto loading_wave_error;
    }
    read(fd, &(file->chunk_size), sizeof(unsigned int));
    read(fd, &(file->format_type), sizeof(short));
    read(fd, &(file->channels), sizeof(short));
    read(fd, &(file->sample_rate), sizeof(unsigned int));
    read(fd, &(file->avg_bytes_per_sec), sizeof(unsigned int));
    read(fd, &(file->bytes_per_sample), sizeof(short));
    read(fd, &(file->bits_per_sample), sizeof(short));
    read(fd, buffer, sizeof(buffer));
    if (strncmp(buffer, "data", sizeof(buffer)) != 0)
    {
        printf("loadWaveFile: missing file data (%s)\n", filepath);
        goto loading_wave_error;
    }
    read(fd, &(file->data_size), sizeof(unsigned int));
    file->data = (unsigned char*)malloc(sizeof(unsigned char) * file->data_size);
    if (file->data == NULL)
    {
        printf("loadWaveFile: not enough memory for file: %s\n", filepath);
        goto loading_wave_error;
    }
    read(fd, file->data, file->data_size * sizeof(unsigned char));
	close(fd);

    if (file->bits_per_sample == 8)
    {
        if (file->channels == 1)
            file->format = AL_FORMAT_MONO8;
        else if (file->channels == 2)
            file->format = AL_FORMAT_STEREO8;
    }
    else if (file->bits_per_sample == 16)
    {
        if (file->channels == 1)
            file->format = AL_FORMAT_MONO16;
        else if (file->channels == 2)
            file->format = AL_FORMAT_STEREO16;
    }
	return (file);

    loading_wave_error:
    close(fd);
    free(file);
    return (NULL);
}

int 	alhCheckError(char const *label)
{
    ALenum	err;

    err = alGetError();
    if (err != AL_NO_ERROR)
    {
        printf("OpenAL error occured: %s: %s\n", label, alGetString(err));
    }
    return (err);
}

void    alhBufferData(ALuint buffer, t_wave_file *file)
{
    alBufferData(buffer, file->format, file->data, file->data_size, file->sample_rate);
}

void    alhSetSound(t_sound_manager *manager, char const *filepath, unsigned soundID)
{
    t_wave_file *file;

    if (soundID >= manager->max_files)
    {
        printf("alhSetSound out of file buffer range, cancelling operation (%u / %u)!\n", soundID, manager->max_files);
        return ;
    }
    file = alhLoadWaveFile(filepath);
    if (file == NULL)
    {
        return ;
    }
    memcpy(manager->files + soundID, file, sizeof(t_wave_file));
    free(file);
}

void    alhPlaySound(t_sound_manager *manager, unsigned soundID, unsigned sourceID)
{
    ALfloat     source_pos[] = {0, 0, 0};
    ALfloat     source_vel[] = {0, 0, 0};

    alhBufferData(manager->internal_buffer, manager->files + soundID);

    alSourcei(manager->sources[sourceID],  AL_BUFFER,              manager->internal_buffer);
    alSourcef(manager->sources[sourceID],  AL_PITCH,               1.0f);
    alSourcef(manager->sources[sourceID],  AL_GAIN,                0.1f);
    alSourcefv(manager->sources[sourceID], AL_POSITION,            source_pos);
    alSourcefv(manager->sources[sourceID], AL_VELOCITY,            source_vel);
    alSourcei(manager->sources[sourceID],  AL_LOOPING,             AL_FALSE);

    alSourcePlay(manager->sources[sourceID]);

    printf("SOUND TEST : %f / %f\n", alGetFloat(AL_MAX_DISTANCE), alGetFloat(AL_REFERENCE_DISTANCE));
}

int 	alhInit(t_sound_manager *manager, unsigned int sources, unsigned int max_files)
{
	char const *dev = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

    manager->sources = (ALuint*)malloc(sizeof(ALuint) * sources);
    if (manager->sources == NULL)
    {
        return (0);
    }
    manager->files = (t_wave_file*)malloc(sizeof(t_wave_file) * max_files);
    if (manager->files == NULL)
    {
        free(manager->sources);
        return (0);
    }
    memset(manager->files, 0, sizeof(t_wave_file) * max_files);
    manager->max_files = max_files;
    manager->sources_count = sources;
    manager->device  = alcOpenDevice(dev);
    if (manager->device == NULL)
    {
    	return (0);
    }
    manager->context = alcCreateContext(manager->device, NULL);
    if (manager->context == NULL)
    {
    	return (0);
    }
    alcMakeContextCurrent(manager->context);
    alGenBuffers(1, &(manager->internal_buffer));
    alGenSources(sources, manager->sources);
    return (1);
}

void	alhStop(t_sound_manager *manager)
{
	unsigned int i;

	alSourceStopv(manager->sources_count, manager->sources);
    for (i = 0; i < manager->sources_count; i++)
    {
    	alSourcei(manager->sources[i], AL_BUFFER, 0);
    }
    for (i = 0 ; i < manager->max_files ; i++)
    {
        if (manager->files + i != NULL)
        {
            alhDeleteWaveFile(manager->files + i);
        }
    }
    alDeleteSources(manager->sources_count, manager->sources);
    alDeleteBuffers(1, &(manager->internal_buffer));
    alcMakeContextCurrent(NULL);
    alcDestroyContext(manager->context);
    alcCloseDevice(manager->device);
    free(manager->sources);
    manager->sources = NULL;
    manager->sources_count = 0;
    manager->device = NULL;
    manager->context = NULL;
}
