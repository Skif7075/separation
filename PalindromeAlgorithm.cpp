#include "PalindromeAlgorithm.h"

#include "Calculations.h"
#include "WordOperations.h"
#include "PermutationOperations.h"
#include <iostream>
#include <time.h>

using namespace std;

void palindromeAlgorithm(int k, Permutation ***automata, int automataCount)
{
	int seconds1 = time(NULL);
	int maxLength = lcm(k);
	for (int curLength = 2; curLength <= maxLength; curLength++)
	{
		cout << endl << "Length " << curLength << endl;
		Permutation ***leftParts = new Permutation**[automataCount];
		for (int i = 0; i < automataCount; i++)
		{
			leftParts[i] = new Permutation*[curLength];
			for (int j = 0; j < curLength; j++)
				leftParts[i][j] = new Permutation(k);
		}
		Permutation ***rightParts = new Permutation**[automataCount];
		for (int i = 0; i < automataCount; i++)
		{
			rightParts[i] = new Permutation*[curLength];
			for (int j = 0; j < curLength; j++)
				rightParts[i][j] = new Permutation(k);
		}
		unsigned int curWord = 1 << (curLength - 1);
		unsigned int bound = (curLength == 32) ? UINT_MAX : (1 << curLength) - 1;

		int differenceInd = 1;
		int *calculated = new int[automataCount];
		for (int i = 0; i < automataCount; i++)
		{
			calculated[i] = 1;
			leftParts[i][0] = new Permutation(*automata[i][1]);
			rightParts[i][0] = new Permutation(*automata[i][1]);
		}
		while (curWord <= bound&&curWord<UINT_MAX)
		{
			differenceInd = (differenceInd < 1) ? 1 : differenceInd;
			for (int i = 0; i < automataCount; i++)
			{
				calculated[i] = (differenceInd<calculated[i]) ? differenceInd : calculated[i];
			}
			unsigned int right = getRightPart(curWord, curLength);
			if (curWord != right && (curWord <= ((~right)&bound)) && (right & 1))
			{
				int curAutomatonInd = 0;
				bool areDifferent = false;
				while (curAutomatonInd < automataCount)
				{
					for (int i = calculated[curAutomatonInd]; i < curLength; i++)
					{
						if ((right&(1 << (i))) == 0)
						{
							calculateNext(leftParts[curAutomatonInd][i], leftParts[curAutomatonInd][i - 1], automata[curAutomatonInd][0], k);
							calculateNext(rightParts[curAutomatonInd][i], automata[curAutomatonInd][0], rightParts[curAutomatonInd][i - 1], k);
						}
						else
						{
							calculateNext(leftParts[curAutomatonInd][i], leftParts[curAutomatonInd][i - 1], automata[curAutomatonInd][1], k);
							calculateNext(rightParts[curAutomatonInd][i], automata[curAutomatonInd][1], rightParts[curAutomatonInd][i - 1], k);
						}
					}
					calculated[curAutomatonInd] = curLength - 1;
					if (!(*leftParts[curAutomatonInd][curLength - 1] == *rightParts[curAutomatonInd][curLength - 1]))
					{
						areDifferent = true;
						break;
					}
					curAutomatonInd++;
				}
				if (!areDifferent)
				{
					int seconds2 = time(NULL);
					printWord(curWord, curLength);
					cout << '=';
					printWord(right, curLength);
					cout << "   in " << (seconds2 - seconds1) << " seconds";
					cout << endl;
					return;
				}
			}
			differenceInd = findDifference(curWord, curWord + 2, curLength);
			curWord += 2;
		}
		for (int i = 0; i < automataCount; i++)
		{
			for (int j = 0; j < curLength; j++)
			{
				delete leftParts[i][j];
				delete rightParts[i][j];
			}
			delete[] leftParts[i];
			delete[] rightParts[i];
		}
		delete[]leftParts;
		delete[]rightParts;
	}
	return;
}