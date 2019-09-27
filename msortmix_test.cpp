//C header files
#include <stdlib.h>
#include <math.h>
#include <time.h>

//C++ header files
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Your own header files
#include "msortmix.h"

int main ( int argc, char* argv[] )
{
	if ( argc != 3 ){
		cout << "Please enter:\n"
		     << "1) ./a.out  in.txt  out.txt\n";
		exit( 1 );
	}

	//input array
	unsigned int N;
	int* values = nullptr;
	bool* isFloatV = nullptr;

	//Read the input array from file
	readArrayMix ( &values, &isFloatV, &N, argv[1] );

	//Sorted array:
	int* sorted = new int[N];
	bool* isFloatS = new bool[N];

	//Sort the input array and report its runtime
	clock_t t1 = clock();
	mergeSortMix ( values, isFloatV, N, sorted, isFloatS );
	clock_t t2 = clock();
	cout << "Runtime=" << (t2-t1)/1000.0 << " ms\n";

	//Write the sorted array into file
	writeArrayMix ( sorted, isFloatS, N, argv[2] );

	return 0;
}
