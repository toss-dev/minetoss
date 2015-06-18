








#include "libft.h"

void startThread()
{
	puts("THREAD: test");
	usleep(1000000);
	puts("THREAD: OK");
	thrd_exit(EXIT_SUCCESS);
}

int	main()
{
	thrd_t t;

	if (thrd_create(&t, (thrd_start_t)startThread, NULL) != thrd_success)
	{
		puts("MAIN: Couldnt create thread");
		return (0);
	}
	int r;
	thrd_join(t, &r);
	puts("MAIN: OK I STOP");
	return (0);
}
