#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "timer.h"

#ifndef SCHOOL
        #define SCHOOL 1000 // number of fish to generate
#endif
#ifndef STEPS
	#define STEPS 1000 // how many iterations to simulate
#endif
#define START_W 10.0 // starting weight of fish
#define MAX_WEIGHT 20.0 // should be 2 x START_W
#define MOVE_SPEED 0.1

int main(int argc, char *argv[])
{
	float max_delta;
	float bary_numer; // technically should have x and y for barycentre
	// but project requirements do not give that equation
	float bary_denom;
	struct fish{
		float x;
		float y;
		float w;
		float euc_dist;
		float delta_f;
	};
	srand(time(NULL));
     	
	// generate fish
	struct fish *fishes;
	fishes = (struct fish*)malloc(SCHOOL*sizeof(struct fish));
	
	for(int i = 0; i<SCHOOL; i = i +1){
		(fishes + i) -> x = 100*(float)rand()/(float)(RAND_MAX) - 50; // randomly in the centre 100x100 square
		(fishes + i) -> y = 100*(float)rand()/(float)(RAND_MAX) - 50;
		(fishes + i) -> w = START_W;
		(fishes + i) -> euc_dist = sqrt(pow((fishes + i) -> x,2) + pow((fishes + i) -> y,2));
	}

	// start the clock
	struct timer_results time_results;
	begin_timer(&time_results);

	// Simulation
	for(int j = 1; j<=STEPS; j = j +1){
		// fish swimming
		for(int i = 0; i<SCHOOL; i = i +1){
			// move random values in interval [-MOVE_SPEED, MOVE_SPEED]
			(fishes + i) -> x = (fishes + i) -> x + (2*(float)rand()/(float)(RAND_MAX) - 1)*MOVE_SPEED;
			(fishes + i) -> y = (fishes + i) -> y + (2*(float)rand()/(float)(RAND_MAX) - 1)*MOVE_SPEED;
			if((fishes + i) -> x > 100.0){
				(fishes + i) -> x = 100.0;
			}
			if((fishes + i) -> x < -100.0){
				(fishes + i) -> x = -100.0;
			}
			if((fishes + i) -> y > 100.0){
				(fishes + i) -> y = 100.0;
			}
			if((fishes + i) -> y < -100.0){
				(fishes + i) -> y = -100.0;
			}
			// use new x and y to calculate change in objective function
			(fishes + i) -> delta_f = sqrt(pow((fishes + i) -> x,2) + pow((fishes + i) -> y,2)) - (fishes + i) -> euc_dist;
			// now calculate new value for objective function
			(fishes + i) -> euc_dist = sqrt(pow((fishes + i) -> x,2) + pow((fishes + i) -> y,2));
		}
			
		// find maximum change to objective function
		max_delta = -0.2; // minimum possible is -0.1*sqrt(2)
		for(int i = 0; i<SCHOOL; i = i +1){
			if((fishes + i) -> delta_f > max_delta){
				max_delta = (fishes + i) -> delta_f;
			}
		}

		//change weights
		for(int i = 0; i<SCHOOL; i = i +1){
			(fishes + i) -> w = (fishes + i) -> w + (fishes + i) -> delta_f/max_delta;
			if((fishes + i) -> w > MAX_WEIGHT){
				(fishes + i) -> w = MAX_WEIGHT;
			}
			if((fishes + i) -> w < 0.0){
				(fishes + i) -> w = 0.0;
			}
		}

		// calculate barycentre
		bary_numer = 0;
		bary_denom = 0;
		for(int i = 0; i<SCHOOL; i = i +1){
			bary_numer = bary_numer + (fishes + i) -> euc_dist * (fishes + i) -> w;
			bary_denom = bary_denom + (fishes + i) -> euc_dist;
		}
	}

	// stop the clock
	end_timer(&time_results);
	printf("sequential,%d,%d,%f,%f,%f,%f\n", SCHOOL, STEPS, time_results.cpu_cycles_elapsed, time_results.omp_elapsed, time_results.monotonic_elapsed, time_results.posix_cputime_elapsed);
}
