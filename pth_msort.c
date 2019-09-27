#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define REP 1


//input array
int* values;
unsigned int M, N;

//sorted array
int* sorted;

void fillarray(int* data, unsigned int N)
{
	unsigned int i;
	for (i = 0; i < N; i++)
		data[i] = rand();
}

void testresult(){} //you need to modify this code!

int main( int argc, char *argv[] )
{
	// N = 2 ^ M
	N = (unsigned int) pow (2.0, 10.0); //you need to modify this code!
	//test M and N:
	printf("M=%d N=%d\n", M, N);
	
	srand(time(0));

	time_t t1, t2;
	double dt; //t2-t1
	double tavg=0.0;

	//input array
	values = (int*) malloc ( sizeof(int) * N );

	int r; for (r = 0; r < REP; r++)
	{
		//fill in the input array with random number
		fillarray(values, N);

		//t1
	        t1 = time(0);
		
		//sort the array
		//parallel merge sort 

		//t2
	        t2 = time(0);

		//t2-t1
	        dt = t2 - t1;

        	//average time
	        tavg += (dt / REP);
	}

	printf ( "%g seconds\n", tavg );

	return 0;
}
