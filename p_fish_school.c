#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<omp.h>

#define SCHOOL 5 // number of fish to generate
#define STEPS 10 // how many iterations to simulate
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
	#pragma omp parallel for
	for(int i = 0; i<SCHOOL; i = i +1){
		(fishes + i) -> x = 100*(float)rand()/(float)(RAND_MAX) - 50; // randomly in the centre 100x100 square
		(fishes + i) -> y = 100*(float)rand()/(float)(RAND_MAX) - 50;
		(fishes + i) -> w = START_W;
		(fishes + i) -> euc_dist = sqrt(pow((fishes + i) -> x,2) + pow((fishes + i) -> y,2));
	}


	// start the clock
	clock_t begin = clock();

	// Simulation
	for(int j = 1; j<=STEPS; j = j +1){
		// fish swimming
		#pragma omp parallel for
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
			printf("fish %u x = %f y = %f delta_f = %f\n", i, (fishes + i) -> x, (fishes + i) -> y, (fishes + i) -> delta_f);
		}
			
		// find maximum change to objective function
		max_delta = -0.2; // minimum possible is -0.1*sqrt(2)
		#pragma omp parallel for reduction(max: max_delta)
		for(int i = 0; i<SCHOOL; i = i +1){
			if((fishes + i) -> delta_f > max_delta){
				max_delta = (fishes + i) -> delta_f;
			}
		}

		printf("max delta_f %f\n", max_delta);

		//change weights
		#pragma omp parallel for
		for(int i = 0; i<SCHOOL; i = i +1){
			(fishes + i) -> w = (fishes + i) -> w + (fishes + i) -> delta_f/max_delta;
			if((fishes + i) -> w > MAX_WEIGHT){
				(fishes + i) -> w = MAX_WEIGHT;
			}
		}

		// calculate barycentre
		bary_numer = 0;
		bary_denom = 0;
		#pragma omp parallel for reduction(+: bary_numer, bary_denom)
		for(int i = 0; i<SCHOOL; i = i +1){
			bary_numer = bary_numer + (fishes + i) -> euc_dist * (fishes + i) -> w;
			bary_denom = bary_denom + (fishes + i) -> euc_dist;
		}
		printf("barycentre =%f | %f | %f\n", bary_numer/bary_denom, bary_numer, bary_denom);
	}

	// stop the clock
	clock_t end = clock();
	printf("Elapsed: %10.6f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

