#include <iostream>
#include "Calculations.h"
#include "PalindromeAlgorithm.h"
#include "ExhaustiveAlgorithm.h"

using namespace std;


Permutation*** generateAutomata(int k,int permutationCount)
{
	int automataCount = permutationCount * permutationCount;
	Permutation ***automata = new Permutation**[automataCount];
	for (int i = 0; i < automataCount; i++)
		automata[i] = new Permutation*[2];
	Permutation t1(k);
	int count = 0;
	for (int i = 0; i < permutationCount; i++)
	{
		Permutation t2(k);
		for (int j = 0; j < permutationCount; j++)
		{
			automata[count][0] = new Permutation(t1);
			automata[count][1] = new Permutation(t2);
			t2.next();
			count++;
		}
		t1.next();
	}
	return automata;
}

void main()
{
	cout << "Input k: ";
	int k;
	cin >> k;
	int permutationCount = fact(k);
	Permutation*** automata = generateAutomata(k, permutationCount);
	int automataCount = permutationCount * permutationCount;
	if (k < 5)
	{
		ExhaustiveAlgorithm algo;
		algo.run(k, automata, automataCount);
	}
	else
		palindromeAlgorithm(k, automata, automataCount);
	system("pause");
	return;
}
