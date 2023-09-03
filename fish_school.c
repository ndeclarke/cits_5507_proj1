#include<ctype.h>
#include<stdlib.h>

void main()
{
	struct fish{
		float x;
		float y;
		float w;
	};

	struct fish *fishes;
	fishes = (struc fish*)malloc(school*sizeof(struc fish));

	fishes -> x=0; // change to random number
	fishes -> y=0;
	fishes -> w=start_w;

	for(i = 1; i<school; i = i +1){
		(fishes + i) -> x=0;
		(fishes + i) -> y=0;
		(fishes + i) -> w=start_w;
	}

}
