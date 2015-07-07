#include "PermutationOperations.h"

Permutation* calculate(Permutation* a, Permutation* b, int* word, int wordLen)
{
	Permutation *r = new Permutation((word[0] == 0) ? *a : *b);
	for (int i = 1; i < wordLen; i++)
	{
		*r * ((word[i] == 0) ? *a : *b);
	}
	return r;
}
Permutation* calculate(Permutation* a, Permutation* b, int word, int wordLen)
{
	Permutation *r = new Permutation(((word & 1) == 0) ? *a : *b);
	for (int i = 1; i < wordLen; i++)
	{
		*r * (((word&(1 << i)) == 0) ? *a : *b);
	}
	return r;
}


void calculateNext(Permutation *a, Permutation *b, Permutation *c, int length)
{
	for (int i = 0; i < length; i++)
		a->arr[i] = c->arr[b->arr[i]];
}
