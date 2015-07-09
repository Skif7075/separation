#include "ExhaustiveAlgorithm.h"

#include "Calculations.h"
#include "PermutationOperations.h"
#include <iostream>

using namespace std;


void ExhaustiveAlgorithm::run(int k, Permutation***automata, int automataCount)
{
	this->automata = automata;
	this->automataCount = automataCount;
	timer = new Timer();
	timer->start();
	int maxLength = lcm(k);
	for (int curLength = 2; curLength <= maxLength; curLength++)
	{
		cout << endl << "Length " << curLength << endl;
		cout << timer->getCurSeconds() << endl;
		int *curWord = new int[curLength];
		for (int i = 0; i < curLength; i++)
		{
			curWord[i] = 0;
		}
		int onesCount = curLength / 2;
		wordsCount = rec(curLength, onesCount);
		allocateMemory(curLength);
		for (int i = 0; i < onesCount; i++)
			curWord[i] = 1;
		goThroughAllWords(curWord, curLength);
		clearMemory();
	}
}

void ExhaustiveAlgorithm::runForAll(int k, Permutation***automata, int automataCount)
{
	this->automata = automata;
	this->automataCount = automataCount;
	timer = new Timer();
	timer->start();
	int maxLength = lcm(k);
	for (int curLength = 2; curLength <= maxLength; curLength++)
	{
		cout << endl << "Length " << curLength << endl;
		cout << timer->getCurSeconds()<< endl;

		int *curWord = new int[curLength];
		for (int i = 0; i < curLength; i++)
		{
			curWord[i] = 0;
		}
		for (int onesCount = 1; onesCount <= curLength / 2; onesCount++)
		{
			wordsCount = rec(curLength, onesCount);
			allocateMemory(curLength);
			for (int i = 0; i < onesCount; i++)
				curWord[i] = 1;
			goThroughAllWords(curWord,curLength);
			clearMemory();			
		}
	}
}

void ExhaustiveAlgorithm::goThroughAllWords(int* curWord, int curLength)
{
	for (int newWordInd = 0; newWordInd < wordsCount; newWordInd++)
	{
		for (int i = 0; i < curLength; i++)
			words[newWordInd][i] = curWord[i];
		compareWordWithPrevious(newWordInd, curLength);
		nextWord(curWord,curLength);
	}
}

void ExhaustiveAlgorithm::clearMemory()
{
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
void ExhaustiveAlgorithm::allocateMemory(int curLength)
{
	words = new int*[wordsCount];
	for (int i = 0; i < wordsCount; i++)
		words[i] = new int[curLength];
	passedCalculationCounters = new int[wordsCount];
	for (int i = 0; i < wordsCount; i++)
		passedCalculationCounters[i] = 0;
	results = new Node*[wordsCount];
	for (int i = 0; i < wordsCount; i++)
		results[i] = new Node();
}
void ExhaustiveAlgorithm::nextWord(int* curWord, int curLength)
{
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
void ExhaustiveAlgorithm::compareWordWithPrevious(int newWordInd,int curLength)
{
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
			cout << "   in " << timer->getCurSeconds() << " seconds";
			cout << endl;
		}
	}
}