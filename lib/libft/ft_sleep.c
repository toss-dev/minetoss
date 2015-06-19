/*
 * ft_sleep.c
 *
 *  Created on: 19 juin 2015
 *      Author: Romain
 */

#include "libft.h"

#ifdef __WIN32
#	include <windows.h>
#else
#	include <unistd.h>
#endif

/** cross platform sleep function in us */
void	ft_sleep(unsigned int us)
{
	#ifdef __WIN32
		HANDLE			timer;
		LARGE_INTEGER	ft;

		ft.QuadPart = -(10 * us); // Convert to 100 nanosecond interval, negative value indicates relative time

		timer = CreateWaitableTimer(NULL, TRUE, NULL);
		SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
		WaitForSingleObject(timer, INFINITE);
		CloseHandle(timer);
    #else
		usleep(us);
	#endif
}
