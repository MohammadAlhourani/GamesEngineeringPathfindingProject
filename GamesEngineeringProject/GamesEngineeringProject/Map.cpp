#include "Map.h"

Map::Map()
{
	square.setFillColor(sf::Color::Red);
	square.setSize(sf::Vector2f(nodeSize, nodeSize));
}

Map::~Map()
{
}

Node Map::getNode(int x, int y)
{
    return Node();
}

Node Map::getNode(sf::Vector2f position)
{
    return Node();
}

void Map::generateMap(MapSize t_size)
{
	Nodes.clear();

	switch (t_size)
	{
	case MapSize::Ten:
	{
		for (int x = 0; x < 30; x++)
		{
			for (int y = 0; y < 30; y++)
			{
				Node* node = new Node(x, y, nodeSize);

				node->setPosition(sf::Vector2f(x * nodeSize, y * nodeSize));

				Nodes.push_back(node);
			}
		}
		break;
	}
	case MapSize::Hundred:
	{
		for (int x = 0; x < 100; x++)
		{
			for (int y = 0; y < 100; y++)
			{
				Node* node = new Node(x, y, nodeSize);

				node->setPosition(sf::Vector2f(x * nodeSize, y * nodeSize));

				Nodes.push_back(node);
			}
		}
		break;
	}
	case MapSize::Thousand:
	{
		for (int x = 0; x < 1000; x++)
		{
			for (int y = 0; y < 1000; y++)
			{
				Node* node = new Node(x, y, nodeSize);

				node->setPosition(sf::Vector2f(x * nodeSize, y * nodeSize));

				Nodes.push_back(node);
			}
		}
		break;
	}
	default:
		break;
	}
}

void Map::draw(sf::RenderWindow& window)
{

	for (auto* node : Nodes)
	{
		square.setPosition(node->getPosition());

		window.draw(square);
	}
}
