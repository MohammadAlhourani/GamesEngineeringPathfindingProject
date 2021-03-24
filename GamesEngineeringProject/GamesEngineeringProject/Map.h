#pragma once


#include "SFML/Graphics.hpp"
#include "Node.h"


class Map
{
public:
	Map();
	~Map();


	Node getNode(int x, int y);

	Node getNode(sf::Vector2f position);

	void generateMap(int t_size);


private:

	int size;


};

