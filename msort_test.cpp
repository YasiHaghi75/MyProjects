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
#include "msort.h"

/*long long int min1;
long long int max1;
long long int sum1;*/

//Dynamically allocate an array of size N in heap
void fillArray ( int** values, unsigned int N )
{
    srand(time(0));

    (*values) = new int[N];

    for (unsigned int i=0; i<N; i++)
        (*values)[i] = rand() - (RAND_MAX/2);
}

//Check to see if the sorted array is really sorted!
void checkArray ( const int* values, unsigned int N, const int* sorted )
{
    for (unsigned int i=0; i <= N-2; i++)
        if (sorted[i]>sorted[i+1])
        {
            cout << "ERROR! i=" << i << " " << sorted[i] << " " << sorted[i+1] << endl;
            return;
        }

    /*//check 2:
    long long int min2 = 0;
    long long int max2 = 0;
    long long int sum2 = 0;
    for (int i=0; i < N; i++)
    {
        s1 += values[i];
        s2 += sorted[i];
    }
    if ( s1!=s2 )
    {
        cout << "ERROR!" << endl;
        return;
    }*/

    cout << "OK!\n";
}

//bool f1 (int x ,int y) {  return ( ( (x%10) > (y%10)) ? true : false); } //for question 3
//bool f2 (int x ,int y) {  return ( ( (x%100) < (y%100)) ? true : false); } //for question 3

int main ( int argc, char* argv[] )
{
    if ( argc != 3 ){
        cout << "Please enter:\n"
             << "1) ./a.out  in.txt  out.txt\n"
             << "or\n"
             << "2) ./a.out  random  M\n";
        exit( 1 );
    }

	//Input is random or from file?
	bool isRandom = ( string(argv[1]).compare("random") == 0 );

	//input array
	unsigned int N;
	int* values = nullptr;

	if ( isRandom ) {
        //Fill in the input array with random data
        N = pow( 2, atoi(argv[2]) );
        fillArray ( &values, N );
    }
    else {
        //Read the input array from file
        readArray ( &values, &N, argv[1] );
    }

	//Sorted array:
	int* sorted = new int[N];

	//Sort the input array and report its runtime
	clock_t t1 = clock();
	mergeSort ( values, N, sorted );
//	mergeSort ( values, N, sorted, f1 ); // for question 3
//	mergeSort ( values, N, sorted, f2 ); // for question 3
	clock_t t2 = clock();
	cout << "Runtime=" << (t2-t1)/1000.0 << " ms\n";

    //Output array
	if ( isRandom ) {
        //Check for correctness
        checkArray ( values, N, sorted );
    }
    else {
        //Write the sorted array into file
        writeArray ( sorted, N, argv[2] );
    }

	return 0;
}
