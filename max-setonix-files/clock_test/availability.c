#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

int main()
{
	struct timespec reso;
#ifdef _POSIX_TIMERS
	printf("posix timers available\n");
#endif

#ifdef _POSIX_MONOTONIC_CLOCK
	printf("Monotonic clock available\n");
	clock_getres(CLOCK_MONOTONIC, &reso);
	printf("reso: %10ld.%09ld\n", (long)reso.tv_sec, reso.tv_nsec);
#endif

#ifdef _POSIX_CPUTIME
	printf("CPU time clock available\n");
	clock_getres(CLOCK_PROCESS_CPUTIME_ID, &reso);
	printf("reso: %10ld.%09ld\n", (long)reso.tv_sec, reso.tv_nsec);
#endif 

#ifdef 	_POSIX_THREAD_CPUTIME
	printf("thread cpu time avaiailable\n");
	clock_getres(CLOCK_THREAD_CPUTIME_ID, &reso);
	printf("reso: %10ld.%09ld\n", (long)reso.tv_sec, reso.tv_nsec);
#endif
}
