#ifndef MSORTMIX
#define MSORTMIX

void readArrayMix  (int** data,      bool** isFloat,      unsigned int* N, const char* filename);
void writeArrayMix (const int* data, const bool* isFloat, unsigned int N,  const char* filename);

void mergeSortMix  (const int* values, const bool* isFloatV, 
                    unsigned int N,
                    int* sorted,       bool* isFloatS);

#endif
