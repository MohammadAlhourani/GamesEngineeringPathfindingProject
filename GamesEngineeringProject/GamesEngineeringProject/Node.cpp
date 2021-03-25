#include "Node.h"

Node::Node()
{
}

Node::Node(int t_x, int t_y, float t_size):
	x(t_x), y(t_y), size(t_size)
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

sf::Vector2f Node::getPosition()
{
	return position;
}

Node* Node::getPrevious()
{
	return previous;
}
