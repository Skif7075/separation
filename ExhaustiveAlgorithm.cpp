#include "ExhaustiveAlgorithm.h"

#include "Calculations.h"
#include "List.h"
#include "PermutationOperations.h"
#include <iostream>
#include "Timer.h"

using namespace std;

void exhaustiveAlgorithm(int k, Permutation***automata, int automataCount)
{
	Timer timer;
	timer.start();
	int maxLength = lcm(k);

	for (int curLength = 2; curLength <= maxLength; curLength++)
	{
		cout << endl << "Length " << curLength << endl;
		cout << timer.getCurSeconds()<< endl;
		int *curWord = new int[curLength];
		for (int i = 0; i < curLength; i++)
		{
			curWord[i] = 0;
		}
		for (int onesCount = 1; onesCount <= curLength / 2; onesCount++)
		{
			int wordsCount = rec(curLength, onesCount);
			int **words = new int*[wordsCount];
			for (int i = 0; i < wordsCount; i++)
				words[i] = new int[curLength];
			int *passedCalculationCounters = new int[wordsCount];
			for (int i = 0; i < wordsCount; i++)
				passedCalculationCounters[i] = 0;
			Node **results = new Node*[wordsCount];
			for (int i = 0; i < wordsCount; i++)
				results[i] = new Node();
			for (int i = 0; i < onesCount; i++)
			{
				curWord[i] = 1;
			}
			for (int newWordInd = 0; newWordInd < wordsCount; newWordInd++)
			{
				for (int i = 0; i < curLength; i++)
					words[newWordInd][i] = curWord[i];
				for (int prevWordInd = 0; prevWordInd < newWordInd - 1; prevWordInd++)
				{
					Node* newWordNode = results[newWordInd];
					Node* prevWordNode = results[prevWordInd];
					int curAutomatonInd = 0;
					bool areDifferent = false;
					while (curAutomatonInd < automataCount)
					{
						if (passedCalculationCounters[newWordInd] <= curAutomatonInd)
						{
							append(newWordNode, calculate(automata[curAutomatonInd][0], automata[curAutomatonInd][1], words[newWordInd], curLength));
							passedCalculationCounters[newWordInd]++;
						}
						if (passedCalculationCounters[prevWordInd] <= curAutomatonInd)
						{
							append(prevWordNode, calculate(automata[curAutomatonInd][0], automata[curAutomatonInd][1], words[prevWordInd], curLength));
							passedCalculationCounters[prevWordInd]++;
						}
						if (!(*(newWordNode->tr) == *(prevWordNode->tr)))
						{
							areDifferent = true;
							break;
						}
						curAutomatonInd++;
						newWordNode = newWordNode->next;
						prevWordNode = prevWordNode->next;
					}
					if (!areDifferent)
					{
						for (int i = 0; i < curLength; i++)
							cout << words[newWordInd][i];
						cout << '=';
						for (int i = 0; i < curLength; i++)
							cout << words[prevWordInd][i];
						cout << "   in " << timer.getCurSeconds() << " seconds";
						cout << endl;
					}
				}
				int prefixOnesCount = 0;
				int letterIndx = 0;
				while (curWord[letterIndx] == 0) letterIndx++;
				while (curWord[letterIndx] != 0 && letterIndx<curLength)
				{
					prefixOnesCount++;
					curWord[letterIndx] = 0;
					letterIndx++;
				}
				curWord[letterIndx] = 1;
				for (int i = 0; i < prefixOnesCount - 1; i++)
					curWord[i] = 1;
			}
			for (int i = 0; i < wordsCount; i++)
				delete[] words[i];
			delete[]words;
			delete[]passedCalculationCounters;
			Node *next;
			for (int j = 0; j < wordsCount; j++)
			{
				Node *root = results[j];
				while (root != NULL)
				{
					next = root->next;
					delete root;
					root = next;
				}
			}
			delete[]results;
		}
	}
}