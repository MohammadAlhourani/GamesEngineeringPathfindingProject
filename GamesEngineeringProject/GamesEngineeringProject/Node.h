#pragma once

#include "SFML/Graphics.hpp"

class Node
{
public:
	Node();
	~Node();

	void CalculateFCost();

	Node* getPrevious();

private:

	int x;
	int y;

	bool passable;

	float pathCost;

	float heuristic;

	float Fcost;

	std::vector<Node*> neighbours;

	Node* previous;

};

