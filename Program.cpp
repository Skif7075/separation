#include <iostream>
#include "Calculations.h"
#include "PalindromeAlgorithm.h"
#include "ExhaustiveAlgorithm.h"

using namespace std;

void main()
{
	cout << "Input k: ";
	int k;
	cin >> k;

	int PermutationCount = fact(k);
	int automataCount = PermutationCount * PermutationCount;
	Permutation ***automata = new Permutation**[automataCount];
	for (int i = 0; i < automataCount; i++)
		automata[i] = new Permutation*[2];
	Permutation t1(k);
	int count = 0;
	for (int i = 0; i < PermutationCount; i++)
	{
		Permutation t2(k);
		for (int j = 0; j < PermutationCount; j++)
		{
			automata[count][0] = new Permutation(t1);
			automata[count][1] = new Permutation(t2);
			t2.next();
			count++;
		}
		t1.next();
	}

	if (k < 6)
		exhaustiveAlgorithm(k, automata, automataCount);
	else
		palindromeAlgorithm(k, automata, automataCount);

	system("pause");
	return;
}


