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
#define NUM_THREADS 4
#define SCHED static

int main(int argc, char *argv[])
{
	float max_delta;
	float bary_numer; // technically should have x and y for barycentre
	// but project requirements do not give that equation
	float bary_denom;

	float *fish_x;
	float *fish_y;
	float *fish_w;
	float *fish_euc_dist;
	float *fish_delta_f;

	srand(time(NULL));
	omp_set_num_threads(NUM_THREADS);
	
	// generate fish
	fish_x = malloc(SCHOOL * sizeof(float));
	fish_y = malloc(SCHOOL * sizeof(float));
	fish_w = malloc(SCHOOL * sizeof(float));
	fish_euc_dist = malloc(SCHOOL * sizeof(float));
	fish_delta_f = malloc(SCHOOL * sizeof(float));

	#pragma omp parallel for schedule(SCHED)
	for(int i = 0; i<SCHOOL; i = i +1){
		fish_x[i] = 100*(float)rand()/(float)(RAND_MAX) - 50; // randomly in the centre 100x100 square
		fish_y[i] = 100*(float)rand()/(float)(RAND_MAX) - 50;
		fish_w[i] = START_W;
		fish_euc_dist[i] = sqrt(pow(fish_x[i], 2) + pow(fish_x[i], 2));
	}

	// start the clock
	clock_t begin = clock();

	// Simulation
	for(int j = 1; j<=STEPS; j = j +1){
		// fish swimming
		#pragma omp parallel for schedule(SCHED)
		for(int i = 0; i<SCHOOL; i = i +1){
			// move random values in interval [-MOVE_SPEED, MOVE_SPEED]
			fish_x[i] = fish_x[i] + (2*(float)rand()/(float)(RAND_MAX) - 1)*MOVE_SPEED;
			fish_y[i] = fish_y[i] + (2*(float)rand()/(float)(RAND_MAX) - 1)*MOVE_SPEED;
			if(fish_x[i] > 100.0){
				fish_x[i] = 100.0;
			}
			if(fish_x[i] < -100.0){
				fish_x[i] = -100.0;
			}
			if(fish_y[i] > 100.0){
				fish_y[i] = 100.0;
			}
			if(fish_y[i] < -100.0){
				fish_y[i] = -100.0;
			}
			// use new x and y to calculate change in objective function
			fish_delta_f[i] = sqrt(pow(fish_x[i],2) + pow(fish_y[i],2)) - fish_euc_dist[i];
			// now calculate new value for objective function
			fish_euc_dist[i] = sqrt(pow(fish_x[i],2) + pow(fish_y[i],2));
		}
			
		// find maximum change to objective function
		max_delta = -0.2; // minimum possible is -0.1*sqrt(2)
		#pragma omp parallel for schedule(SCHED) reduction(max: max_delta)
		for(int i = 0; i<SCHOOL; i = i +1){
			if(fish_delta_f[i] > max_delta){
				max_delta = fish_delta_f[i];
			}
		}

		//change weights
		#pragma omp parallel for schedule(SCHED)
		for(int i = 0; i<SCHOOL; i = i +1){
			fish_w[i] = fish_w[i] + fish_delta_f[i]/max_delta;
			if(fish_w[i] > MAX_WEIGHT){
				fish_w[i] = MAX_WEIGHT;
			}
			if(fish_w[i] < 0.0){
				fish_w[i] = 0.0;
			}
		}

		// calculate barycentre
		bary_numer = 0;
		bary_denom = 0;
		#pragma omp parallel for schedule(SCHED) reduction(+: bary_numer, bary_denom)
		for(int i = 0; i<SCHOOL; i = i +1){
			bary_numer = bary_numer + fish_euc_dist[i] * fish_w[i];
			bary_denom = bary_denom + fish_euc_dist[i];
		}
		printf("barycentre =%f | %f | %f\n", bary_numer/bary_denom, bary_numer, bary_denom);
	}

	// stop the clock
	clock_t end = clock();
	printf("Elapsed: %10.6f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

