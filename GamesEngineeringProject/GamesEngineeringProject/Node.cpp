#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::CalculateFCost()
{
	Fcost = heuristic + pathCost;
}

Node* Node::getPrevious()
{
	return previous;
}
