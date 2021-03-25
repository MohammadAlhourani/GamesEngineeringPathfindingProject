#pragma once


#include "SFML/Graphics.hpp"
#include "Node.h"

enum class MapSize
{
	Ten,
	Hundred,
	Thousand
};


class Map
{
public:
	Map();
	~Map();


	Node getNode(int x, int y);

	Node getNode(sf::Vector2f position);

	void generateMap(MapSize t_size);

	void draw(sf::RenderWindow& window);


private:

	MapSize size;

	std::vector<Node*> Nodes;

	float nodeSize = 1;


	sf::RectangleShape square;
};

