#include "sorter.h"
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "timer.h"
#include <assert.h>
#include <stdbool.h>

#define SCHOOL 10000000
#define START_W 10

static void correctness(struct fish *fishes)
{
	assert(fishes[0].x < fishes[SCHOOL - 1L].x);
	assert(fishes[1000].x < fishes[SCHOOL - 1000L].x);
	/*
	for (long i = 0; i < SCHOOL - 2; i++)
	{
		if ((fishes + i)->x < (fishes + i + 1)->x) {
			printf("%f not < than %f\n", (fishes + i)->x, (fishes + i + 1)->x);
			assert(false);
		}
	}
	*/
}

static void display_fishes(struct fish *fishes)
{
	for (int i = 0; i < SCHOOL; i++)
	{
		printf("%f,%f,%f,%f,%f\n", fishes[i].x, fishes[i].y, fishes[i].w, fishes[i].euc_dist, fishes[i].delta_f);
	}
}

int main()
{
	struct timer_results res;
	struct fish *fishes = malloc(SCHOOL * sizeof(struct fish));
	for(long i = 0; i<SCHOOL; i = i +1){
		(fishes + i) -> x = 100*(float)rand()/(float)(RAND_MAX) - 50; // randomly in the centre 100x100 square
		(fishes + i) -> y = 100*(float)rand()/(float)(RAND_MAX) - 50;
		(fishes + i) -> w = START_W;
		(fishes + i) -> euc_dist = sqrt(pow((fishes + i) -> x,2) + pow((fishes + i) -> y,2));
	}
	printf("\nseq:\n");
	begin_timer(&res);
	seq_quick_sort(fishes, 0, SCHOOL - 1);
	end_timer(&res);
	correctness(fishes);
	printf("%f,%f\n", res.cpu_cycles_elapsed, res.monotonic_elapsed);
	printf("\n\n");
	for (int i = 0; i < SCHOOL; i = i +1){
		(fishes + i) -> x = 100*(float)rand()/(float)(RAND_MAX) - 50; // randomly in the centre 100x100 square
		(fishes + i) -> y = 100*(float)rand()/(float)(RAND_MAX) - 50;
		(fishes + i) -> w = START_W;
		(fishes + i) -> euc_dist = sqrt(pow((fishes + i) -> x,2) + pow((fishes + i) -> y,2));
	}
	printf("\npar:\n");
	begin_timer(&res);
	par_quick_sort(fishes, 0, SCHOOL - 1);
	end_timer(&res);
	correctness(fishes);
	printf("%f,%f\n", res.cpu_cycles_elapsed, res.monotonic_elapsed);
}
