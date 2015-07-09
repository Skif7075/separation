#ifndef Exhaustive_Algorithm_h
#define Exhaustive_Algorithm_h

#include "Permutation.h";
#include "Timer.h";
#include "List.h";

class ExhaustiveAlgorithm
{
private:
	int** words;
	int wordsCount;
	Permutation*** automata;
	int automataCount;
	int *passedCalculationCounters;
	Node **results;
	Timer* timer;
	void goThroughAllWords(int*, int);
	void compareWordWithPrevious(int,int);
	void clearMemory();
	void allocateMemory(int);
	void nextWord(int* curWord, int curLength);
public:
	void run(int, Permutation***, int);
	void runForAll(int, Permutation***, int);
};

#endif