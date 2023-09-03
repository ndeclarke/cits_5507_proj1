#include<ctype.h>
#include<stdlib.h>

static int school = 5; // number of fish to generate
static float start_w = 10.0; // starting weight of fish, also half of the max weight
static float move_speed = 0.1;
static int max_steps = 10; // how many iterations of swimming to simulate

void main()
{
	float max_delta;
	struct fish{
		float x;
		float y;
		float w;
		float move_x;
		float move_y;
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
			(fishes + i) -> delta_f = sqrt((x + move_x)**2 + (y + move_y)**2) - sqrt(x**2 + y**2);
			(fishes + i) -> x = x + move_x;
			(fishes + i) -> y = y + move_y;
		}
		// find maximum change to objective function
		max_delta = -0.2 // minimum possible is 0.1*sqrt(2)
		for(i = 0; i<school; i = i +1){
			if((fishes + i).delta_f > max_delta){max_delta = (fishes + i).delta_f;
		}
		//change weights
		for(i = 0; i<school; i = i +1){
			(fishes + i) -> w = w + delta_f/max_delta;
		}
		// calculate barycentre
		for(i = 0; i<school; i = i +1){
			//sum
		}
	}
}

