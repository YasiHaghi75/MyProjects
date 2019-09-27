#ifndef MSORT
#define MSORT

void readArray  (int** data,        unsigned int* N, const char* filename);
void writeArray (const int* data,   unsigned int N,  const char* filename);
void mergeSort  (const int* values, unsigned int N,  int* sorted, bool (*isSorted)(int,int)=nullptr);

#endif
