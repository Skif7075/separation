#ifndef Permutation_Operations_h
#define Permutation_Operations_h

#include "Permutation.h"

Permutation* calculate(Permutation* a, Permutation* b, int* word, int wordLen);
Permutation* calculate(Permutation* a, Permutation* b, int word, int wordLen);
void calculateNext(Permutation *a, Permutation *b, Permutation *c, int length);

#endif