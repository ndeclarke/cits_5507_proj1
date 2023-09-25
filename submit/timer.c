#include "timer.h"
#include <omp.h>
#include <time.h>
#include <assert.h>

static double convert_timespec(struct timespec spec)
{
	return (double)spec.tv_sec + 0.000000001*spec.tv_nsec;	
}

static int begun_timing = 0;
void begin_timer(struct timer_results *results)
{
	assert(begun_timing == 0);
	results->cpu_cycles_elapsed = clock();
	results->omp_elapsed = omp_get_wtime();
	struct timespec spec;
	assert(clock_gettime(CLOCK_MONOTONIC, &spec) != -1);
	results->monotonic_elapsed = convert_timespec(spec);
	assert(clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &spec) != -1);
	results->posix_cputime_elapsed = convert_timespec(spec);
	begun_timing = 1;
}

void end_timer(struct timer_results *results)
{
	assert(begun_timing == 1);
	results->cpu_cycles_elapsed = (clock() - results->cpu_cycles_elapsed)/CLOCKS_PER_SEC;
	results->omp_elapsed = omp_get_wtime() - results->omp_elapsed;
	struct timespec spec;
	assert(clock_gettime(CLOCK_MONOTONIC, &spec) != -1);
	results->monotonic_elapsed = convert_timespec(spec) - results->monotonic_elapsed;
	assert(clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &spec) != -1);
	results->posix_cputime_elapsed = convert_timespec(spec) - results->posix_cputime_elapsed;
	begun_timing = 0;
}
