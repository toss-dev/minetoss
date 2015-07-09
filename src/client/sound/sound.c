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

#include "client/main.h"

static void placeListener(t_camera *camera)
{
	ALfloat	pos[] = {camera->pos.x, camera->pos.y, camera->pos.z};
	ALfloat	vel[] = {0, 0, 0};
	ALfloat	dir[] = {0, 0, -1, 0, 1, 0};

	alListenerfv(AL_POSITION, 		pos);
 	alListenerfv(AL_VELOCITY, 		vel);
 	alListenerfv(AL_ORIENTATION, 	dir);
}

void 	updateSound(t_sound_manager *manager, t_camera *camera)
{
	static int i = 0;

	placeListener(camera);

	if (i == 0)
	{
		alhPlaySound(manager, SOUND_KALIMBA, SOUND_SOURCE_MUSIC);
		i = 1;
	}

	alhCheckError("update");
}

void 	initSound(t_sound_manager *manager)
{
	alhInit(manager, SOUND_SOURCE_MAX, SOUND_MAX);
	alhSetSound(manager, "./assets/sounds/Kalimba.wav", SOUND_KALIMBA);
}