#include "WordOperations.h"
#include <iostream>

using namespace std;
bool isPalindromicInt(int a, int length)
{
	int i = 0;
	int j = length - 1;
	while (i < j) {
		if (((a&(1 << i++)) ? 1 : 0) != ((a&(1 << j--)) ? 1 : 0)) {
			return false;
		}
	}
	return true;
}

void printWord(unsigned int word, int length)
{
	for (int y = 0; y < length; y++)
		cout << ((word&(1 << length - 1 - y)) != 0) ? 1 : 0;
}
int findDifference(int word1, int word2, int length)
{
	for (int i = length - 1; i >= 0; i--)
		if (word1 >> i != word2 >> i)
			return length - i - 1;
	return length;
}

int getRightPart(int word, int length)
{
	int result = 0;
	for (int i = 0; i < length; i++)
		if (word&(1 << i))
		{
		result |= (1 << (length - 1 - i));
		}
	return result;
}