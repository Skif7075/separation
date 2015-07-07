#ifndef List_h
#define List_h

#include "Permutation.h"

class Node
{
public:
	Permutation* tr;
	Node* next;
	Node();
	~Node();
};
void append(Node*, Permutation*);

#endif