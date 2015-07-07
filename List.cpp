#include "List.h"

#define NULL 0

using namespace std;

Node::Node()
{
	this->tr = NULL;
	this->next = NULL;
}
Node::~Node()
{
	delete tr;
}

void append(Node* node, Permutation* tr)
{
	if (node->tr == NULL)
	{
		node->tr = tr;
		node->next = new Node();
		return;
	}
	append(node->next, tr);
}
