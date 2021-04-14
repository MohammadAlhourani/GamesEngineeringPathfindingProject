#include "Node.h"

Node::Node()
{
}

Node::Node(int t_x, int t_y, float t_size):
	x(t_x), y(t_y), size(t_size) , neighbours(new std::vector<Node*>())
{
}

Node::~Node()
{
}

void Node::CalculateFCost()
{
	fcost = heuristic + pathCost;
}

void Node::setPosition(sf::Vector2f t_pos)
{
	position = t_pos;
}

void Node::addNeighbour(Node* t_node)
{
	neighbours->push_back(t_node);
}

std::vector<Node*>* Node::getNeighbours()
{
	return neighbours;
}

sf::Vector2f Node::getPosition()
{
	return position;
}

Node* Node::getPrevious()
{
	return previous;
}
