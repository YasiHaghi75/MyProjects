//C header files
#include <stdlib.h>
#include <math.h>

//C++ header files
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Your own header files
#include "msort.h"

//TODO: Add preprocessor directives to the following line
#ifndef BLOCKSIZE
#define BLOCKSIZE 16
#endif

void readArray(int** data, unsigned int* N, const char* filename)
{
	ifstream myfile(filename);

	if (!myfile.is_open())
	{
		cout << "Unable to open input file!\n";
		exit(1);
	}

	bool firstline = true;
	string line;
	unsigned int i = 0;

	while (getline(myfile, line))
	{
		if (firstline)
		{
			//first line: N
			firstline = false;
			*N = pow ( 2, stoi(line) );

			//allocate the int array
			*data = new int[*N];
		}
		else
		{
			//other lines: values
			(*data)[i] = stoi(line);
			i++;
		}
	}

	if (i != *N)
	{
		cout << "Corrupted file!\n";
		exit(1);
	}

	myfile.close();
}

void writeArray(const int* data, unsigned int N, const char* filename)
{
	ofstream myfile(filename);

	if (!myfile.is_open())
	{
		cout << "Unable to open output file!\n";
		exit(1);
	}

	myfile << N << endl;

	for (unsigned int i = 0; i < N; i++)
	{
		myfile << data[i] << endl;
	}

	myfile.close();
}

//TODO: Implement the merge sort function here.
//Note: You may add any additional functions you need to this file.
//      Don't change msort.h and msort_test.cpp
bool smaller(int x, int y){
	return(x<y);
}
void bubbleSort( int arr[], int iBegin,int iEnd,bool (*isSorted)(int,int))
{
   int i, j,temp;
   int k=0;
   for (i = iBegin; i < iEnd; i++)        
      { for (j = iBegin; j < iEnd-k; j++) 
           {if (isSorted(arr[j+1],arr[j]))
           {
           	temp=arr[j+1];
           	arr[j+1]=arr[j];
           	arr[j]=temp;
		   }
              }
        k++;
       }
   return ;
    
              
}
void TopDownMerge( int A[], int iBegin, int iMiddle, int iEnd,bool (*isSorted)(int,int))
{ int i,j,k;
int n1=iMiddle-iBegin+1;
int n2=iEnd-iMiddle;
int *L=new int [n1];
int *R=new int [n2];
for(i=0;i<n1;i++)
{L[i]=A[iBegin+i];
R[i]=A[iMiddle+1+i];}
i=0;
j=0;
k=iBegin;
while(i<n1 && j<n2)
{
	if((L[i]==R[j]) || (isSorted(L[i],R[j])))
	{
		A[k]=L[i];
		i++;
	}
	else
	{
		A[k]=R[j];
		j++;
	}
	k++;
}
while(i<n1)
{
	A[k]=L[i];
	i++;
	k++;
}
while(j<n2)
{
	A[k]=R[j];
	j++;
	k++;
}

delete [] L;
delete [] R;

    return;
}
void TopDownSplitMerge( int A[],int iBegin,int iEnd,bool (*isSorted)(int,int))
{
    if(iEnd - iBegin   < BLOCKSIZE)
	{bubbleSort(A,iBegin,iEnd,isSorted) ;
        return;}
	                                 
    int iMiddle = (iEnd + iBegin-1) / 2;              
    TopDownSplitMerge(A, iBegin,  iMiddle,isSorted);  
    TopDownSplitMerge(A, iMiddle +1,    iEnd,isSorted);  
    TopDownMerge(A, iBegin, iMiddle, iEnd,isSorted);
}
void mergeSort(const int* values, unsigned int N, int* sorted, bool (*isSorted)(int,int))
{
    //Report N and BLOCKSIZE
    cout << "N=" << N << " BLOCKSIZE=" << BLOCKSIZE << endl;
    
    

    for (unsigned int i=0; i<N; i++)
    {
        sorted[i] = values[i];
    }
    if(isSorted==nullptr)
    TopDownSplitMerge(sorted,0,N-1,smaller);
    else
    TopDownSplitMerge(sorted,0,N-1,isSorted);
}

