//C header files
#include <stdlib.h>
#include <math.h>

//C++ header files
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Your own header files
#include "msortmix.h"

//TODO: Add preprocessor directives to the following line
#ifndef BLOCKSIZE
#define BLOCKSIZE 128
#endif

void readArrayMix(int** data,bool** isFloat, unsigned int* N, const char* filename)
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
	unsigned int j = 0;
	int show;
	float Fdata;

	while (getline(myfile, line))
	{
		if (firstline)
		{
			//first line: N
			firstline = false;
			*N = pow ( 2, stoi(line) );

			//allocate the int array
			*data = new int[*N];
			*isFloat=new bool[*N];
			
		}
		else
		{
			//other lines: values
			show=line.find(".");
			if(show==-1)
			{(*data)[i] = stoi(line);
			 (*isFloat)[i]=false;
			i++;}
			else
			{ 
			  Fdata=stof(line);
			 (*data)[i]=*((int*)(&Fdata));
			  (*isFloat)[i]=true;
			  i++;
			  j++;
			}
		}
	}

	if (i != *N)
	{
		cout << "Corrupted file!\n";
		exit(1);
	}

	myfile.close();
}

void writeArrayMix(const int* data,const bool* isFloat ,unsigned int N, const char* filename)
{
	ofstream myfile(filename);

	if (!myfile.is_open())
	{
		cout << "Unable to open output file!\n";
		exit(1);
	}

	myfile << N << endl;
     float* temp;
	for (unsigned int i = 0; i < N; i++)
	{   if(isFloat[i]==true)
	    {temp=(float*)(data+i);
	    myfile << *temp <<endl;}
	    else
		myfile << data[i] << endl;
	}

	myfile.close();
}

//TODO: Implement the merge sort function here.
//Note: You may add any additional functions you need to this file.
//      Don't change msort.h and msort_test.cpp
void bubbleSort( int arr[], int iBegin,int iEnd,bool isFloat[])
{
   int i, j,temp;
   float *temp1;
   float *temp2;
   bool s;
   int k=0;
   for (i = iBegin; i < iEnd; i++)          
      { for (j = iBegin; j < iEnd-k; j++) 
           {if( (isFloat[j]==true) && (isFloat[j+1]==true) )
           {
           	temp1=(float*)(arr+j);
           	temp2=(float*)(arr+j+1);
           	if (*temp1 > *temp2)
           {
           	temp=arr[j+1];
           	s=isFloat[j+1];
           	arr[j+1]=arr[j];
           	isFloat[j+1]=isFloat[j];
           	arr[j]=temp;
           	isFloat[j]=s;
		   }
		   }
            else if( (isFloat[j]==false) && (isFloat[j+1]==true) )
            {
           	temp2=(float*)(arr+j+1);
           	if (arr[j] > *temp2)
           {
           	temp=arr[j+1];
           	s=isFloat[j+1];
           	arr[j+1]=arr[j];
           	isFloat[j+1]=isFloat[j];
           	arr[j]=temp;
           	isFloat[j]=s;
		   }
		   }
            else if( (isFloat[j]==true) && (isFloat[j+1]==false) )
            {
           	temp1=(float*)(arr+j);
           	if ( *temp1 > arr[j+1])
           {
           	temp=arr[j+1];
           	s=isFloat[j+1];
           	arr[j+1]=arr[j];
           	isFloat[j+1]=isFloat[j];
           	arr[j]=temp;
           	isFloat[j]=s;
		   }
		   }
		   
		  else
		  { 
		   if (arr[j] > arr[j+1])
           {
           	temp=arr[j+1];
           	s=isFloat[j+1];
           	arr[j+1]=arr[j];
           	isFloat[j+1]=isFloat[j];
           	arr[j]=temp;
           	isFloat[j]=s;
		   }
              }}
        k++;
       }
    
   return ;
    
              
}
void TopDownMerge( int A[], int iBegin, int iMiddle, int iEnd,bool isFloat[])
{ int i,j,k;
int n1=iMiddle-iBegin+1;
int n2=iEnd-iMiddle;
int *L=new int [n1];
int *R=new int [n2];
bool *sL=new bool[n1];
bool *sR=new bool[n2];
float *temp1;
float *temp2;
for(i=0;i<n1;i++)
{L[i]=A[iBegin+i];
sL[i]=isFloat[iBegin+i];
R[i]=A[iMiddle+1+i];
sR[i]=isFloat[iMiddle+1+i];}
i=0;
j=0;
k=iBegin;
while(i<n1 && j<n2)
{if( (sL[i]==true) && (sR[j]==true) ){
	temp1=(float*)(L+i);
   	temp2=(float*)(R+j);
	if(*temp1<=*temp2)
	{   
		A[k]=L[i];
		isFloat[k]=sL[i];
		i++;
	}
	else
	{   
		A[k]=R[j];
		isFloat[k]=sR[j];
		j++;
	}
	k++;
}
else if( (sL[i]==true) && (sR[j]==false) ) {
	temp1=(float*)(L+i);
	if(*temp1<=R[j])
	{   isFloat[k]=sL[i];
		A[k]=L[i];
		i++;
	}
	else
	{   isFloat[k]=sR[j];
		A[k]=R[j];
		j++;
	}
	k++;
}
else if( (sL[i]==false) && (sR[j]==true)  ){
	temp1=(float*)(R+j);
	if(L[i]<=*temp1)
	{   isFloat[k]=sL[i];
		A[k]=L[i];
		i++;
	}
	else
	{   isFloat[k]=sR[j];
		A[k]=R[j];
		j++;
	}
	k++;
}
else{
	if(L[i]<=R[j])
	{   isFloat[k]=sL[i];
		A[k]=L[i];
		i++;
	}
	else
	{   isFloat[k]=sR[j];
		A[k]=R[j];
		j++;
	}
	k++;
}}
while(i<n1)
{
	A[k]=L[i];
	isFloat[k]=sL[i];
	i++;
	k++;
}
while(j<n2)
{
	A[k]=R[j];
	isFloat[k]=sR[j];
	j++;
	k++;
}

delete [] L;
delete [] R;
delete [] sR;
delete [] sL;

    return;
}
void TopDownSplitMerge( int A[],int iBegin,int iEnd,bool vi[])
{
    if(iEnd - iBegin   < BLOCKSIZE)
	{bubbleSort(A,iBegin,iEnd,vi) ;
        return;}
	                                 
    int iMiddle = (iEnd + iBegin-1) / 2;              
    TopDownSplitMerge(A, iBegin,  iMiddle,vi);  
    TopDownSplitMerge(A, iMiddle +1,    iEnd,vi);  
    TopDownMerge(A, iBegin, iMiddle, iEnd,vi);
}
void mergeSortMix(const int* values,const bool* isFloatV ,unsigned int N, int* sorted,bool* isFloats )
{
    //Report N and BLOCKSIZE
    cout << "N=" << N << " BLOCKSIZE=" << BLOCKSIZE << endl;

    for (unsigned int i=0; i<N; i++)
    {
        sorted[i] = values[i];
        isFloats[i]=isFloatV[i];
    }
    TopDownSplitMerge(sorted,0,N-1,isFloats);
}

