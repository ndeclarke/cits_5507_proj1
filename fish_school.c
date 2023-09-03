#include<ctype.h>
#include<stdlib.h>

static int school = 5; // number of fish to generate
static float start_w = 10.0; // starting weight of fish, also half of the max weight
static float move_speed = 0.1;
static int max_steps = 10; // how many iterations of swimming to simulate

void main()
{
	float max_delta;
	float bary_numer; // technically should have x and y for barycentre
	// but project requirements do not give that equation
	float bary_denom;
	struct fish{
		float x;
		float y;
		float w;
		float move_x;
		float move_y;
		float euc_dist;
		float delta_f;
	};
	
	// generate fish
	struct fish *fishes;
	fishes = (struc fish*)malloc(school*sizeof(struc fish));

	for(i = 0; i<school; i = i +1){
		(fishes + i) -> x = 50*(float)rand()/(float)(RAND_MAX);
		(fishes + i) -> y = 50*(float)rand()/(float)(RAND_MAX);
		(fishes + i) -> w=start_w;
	}

	for(j = 1; j<=max_steps; j = j +1){
		// fish swimming
		for(i = 0; i<school; i = i +1){
			(fishes + i) -> move_x = ((float)rand()/(float)(RAND_MAX)-0.5)*move_speed;
			(fishes + i) -> move_y = ((float)rand()/(float)(RAND_MAX)-0.5)*move_speed;
			(fishes + i) -> x = (fishes + i) -> x + (fishes + i) -> move_x;
			(fishes + i) -> y = (fishes + i) -> y + (fishes + i) -> move_y;
			(fishes + i) -> delta_f = sqrt((fishes + i) -> x**2 + (fishes + i) -> move_y**2) - (fishes + i) -> euc_dist;
			(fishes + i) -> euc_dist = sqrt((fishes + i) -> x**2 + (fishes + i) -> move_y**2);
		}

		// find maximum change to objective function
		max_delta = -0.2 // minimum possible is 0.1*sqrt(2)
		for(i = 0; i<school; i = i +1){
			if((fishes + i) -> delta_f > max_delta){max_delta = (fishes + i) -> delta_f;}
		}

		//change weights
		for(i = 0; i<school; i = i +1){
			(fishes + i) -> w = w + (fishes + i) -> delta_f/max_delta;
		}

		// calculate barycentre
		bary_numer = 0;
		bary_denom = 0;
		for(i = 0; i<school; i = i +1){
			bary_numer = bary_numer + (fishes + i) -> euc_dist * (fishes + i) -> w;
			bary_denom = bary_denom + (fishes + i) -> euc_dist;
		}
		printf("barycentre =%f\n", bary_numer/bary_denom);
	}
}

