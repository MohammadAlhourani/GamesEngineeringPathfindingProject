#pragma once

#include "SFML/Graphics.hpp"

class Node
{
public:
	Node();

	Node(int t_x, int t_y, float t_size = 1);

	~Node();

	void CalculateFCost();

	void setPosition(sf::Vector2f t_pos);

	void addNeighbour(Node* t_node);

	std::vector<Node*>* getNeighbours();

	sf::Vector2f getPosition();

	Node* getPrevious();

	int x;
	int y;

	float fcost;

	float pathCost;

	float heuristic;

	bool passable;

	Node* previous;

	bool marked = false;

private:

	float size;	

	sf::Vector2f position;

	std::vector<Node*>* neighbours;

	

};

