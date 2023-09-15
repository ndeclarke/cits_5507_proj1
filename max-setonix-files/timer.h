#ifndef timer_h
#define timer_h

struct timer_results
{
	double cpu_cycles_elapsed;
	double omp_elapsed;
	double monotonic_elapsed;
	double posix_cputime_elapsed;
};

void begin_timer(struct timer_results *results);
void end_timer(struct timer_results *results);

#endif//timer_h
