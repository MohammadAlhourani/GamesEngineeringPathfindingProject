#include "Map.h"

Map::Map()
{
	square.setFillColor(sf::Color::Red);
	square.setOutlineColor(sf::Color::Black);
}

Map::~Map()
{
}

Node* Map::getNode(int t_x, int t_y)
{

	return Nodes.at(int(t_y + (t_x * Row)));
}

Node* Map::getNode(sf::Vector2f position)
{
    return nullptr;
}

void Map::generateMap(MapSize t_size)
{
	Nodes.clear();

	switch (t_size)
	{
	case MapSize::Ten:
	{
		Row = 30;
		Col = 30;

		int index = 0;

		for (int x = 0; x < Row; x++)
		{
			for (int y = 0; y < Col; y++)
			{
				Node* node = new Node(x, y, nodeSize);

				node->setPosition(sf::Vector2f(x * (SCREEN_WIDTH / Row), y * (SCREEN_HEIGHT / Col)));

				Nodes.push_back(node);

			}
		}

		getNeighbour();			

		setupWalls(t_size);

		square.setSize(sf::Vector2f(SCREEN_WIDTH / Row, SCREEN_HEIGHT / Col));
		square.setOutlineThickness(1);

		break;
	}
	case MapSize::Hundred:
	{
		Row = 100;
		Col = 100;

		int index = 0;

		for (int x = 0; x < Row; x++)
		{
			for (int y = 0; y < Col; y++)
			{
				Node* node = new Node(x, y, nodeSize);

				node->setPosition(sf::Vector2f(x * (SCREEN_WIDTH / Row), y * (SCREEN_HEIGHT / Col)));

				Nodes.push_back(node);
			}
		}

		getNeighbour();
		setupWalls(t_size);

		square.setSize(sf::Vector2f(SCREEN_WIDTH / Row, SCREEN_HEIGHT / Col));
		square.setOutlineThickness(1);

		break;
	}
	case MapSize::Thousand:
	{

		Row = 1000;
		Col = 1000;

		int index = 0;

		for (int x = 0; x < Row; x++)
		{
			for (int y = 0; y < Col; y++)
			{
				Node* node = new Node(x, y, nodeSize);

				node->setPosition(sf::Vector2f(x * (SCREEN_WIDTH / Row), y * (SCREEN_HEIGHT / Col)));

				Nodes.push_back(node);
			}
		}

		getNeighbour();
		setupWalls(t_size);

		square.setSize(sf::Vector2f(SCREEN_WIDTH / Row, SCREEN_HEIGHT / Col));
		square.setOutlineThickness(0);
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

		if (node->passable == true)
		{
			square.setFillColor(sf::Color::Red);
		}
		else
		{
			square.setFillColor(sf::Color::Green);
		}

		window.draw(square);
	}
}

std::vector<Node*> Map::AstarPathFind(Node* t_start, Node* t_goal)
{
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;

	std::list<Node*> closedList;


	t_start->pathCost = 0;
	t_start->heuristic = calHueristic(t_start, t_goal);
	t_start->CalculateFCost();

	pq.push(t_start);


	while (pq.size() != 0)
	{
		Node* currentNode = pq.top();

		if (currentNode == t_goal)
		{
			calPath(t_goal);
		}

		pq.pop();
		closedList.push_back(currentNode);

		for (auto* neighbourNode : *currentNode->getNeighbours())
		{
			//closedList.
			if (std::find(closedList.begin(), closedList.end(), neighbourNode) != closedList.end())
			{
				continue;
			}

			if (neighbourNode->passable == false)
			{
				closedList.push_back(neighbourNode);
				continue;
			}

			int tentativeGCost = currentNode->pathCost + calHueristic(currentNode, neighbourNode);

			if (tentativeGCost < neighbourNode->pathCost)
			{
				neighbourNode->previous = currentNode;
				neighbourNode->pathCost = tentativeGCost;
				neighbourNode->heuristic = calHueristic(neighbourNode, t_goal);
				neighbourNode->CalculateFCost();

				if (neighbourNode->marked == false)
				{
					pq.push(neighbourNode);
					neighbourNode->marked = true;
				}		
				
			}
		}
		
		
	}

	return std::vector<Node*>();
}

int Map::calHueristic(Node* t_node1, Node* t_node2)
{
	int xDistance = abs(t_node1->getPosition().x - t_node2->getPosition().x);

	int yDistance = abs(t_node1->getPosition().y - t_node2->getPosition().y);

	int remaining = abs(xDistance - yDistance);

	return MOVE_DIAGONAL * std::min(xDistance,yDistance) + MOVE_STRAIGHT * remaining;
}

void Map::getNeighbour()
{
	for (auto* node : Nodes)
	{
		// List all neighbors:
		for (int direction = 0; direction < 9; direction++)
		{
			if (direction == 4) continue; // Skip 4, this is ourself.

			int n_row = node->x + ((direction % 3) - 1); // Neighbor row
			int n_col = node->y + ((direction / 3) - 1); // Neighbor column

			// Check the bounds:
			if (n_row >= 0 && n_row < Row && n_col >= 0 && n_col < Col)
			{
				//find the neighbour nodes by checking the row and col against the nodes row and col in the graph
				int nodeIndex = int(node->y + (node->x * Row));

				if (Nodes.at(nodeIndex)->x == n_row &&
					Nodes.at(nodeIndex)->y == n_col)
				{
					node->addNeighbour(Nodes.at(nodeIndex));
				}
			}
		}
	}
}

void Map::getNeighbour(Node* t_node)
{
	std::vector<Node*> neighbours;

	if (t_node->x - 1 >= 0)
	{
		//left 0
		neighbours.push_back(getNode(t_node->x - 1, t_node->y)); 

		//left down 
		if (t_node->y - 1 >= 0)
		{
			neighbours.push_back(getNode(t_node->x - 1, t_node->y - 1));
		}

		//left up 
		if (t_node->y + 1 < Col)
		{
			neighbours.push_back(getNode(t_node->x - 1, t_node->y + 1));
		}

	}

	if (t_node->x + 1 < Row)
	{
		//right
		neighbours.push_back(getNode(t_node->x + 1, t_node->y));

		//right down
		if (t_node->y - 1 >= 0)
		{
			neighbours.push_back(getNode(t_node->x + 1, t_node->y - 1));
		}

		//right up
		if (t_node->y + 1 < Col)
		{
			neighbours.push_back(getNode(t_node->x + 1, t_node->y + 1));
		}
	}

	//down
	if (t_node->y - 1 >= 0)
	{
		neighbours.push_back(getNode(t_node->x, t_node->y - 1));
	}

	//up
	if (t_node->y + 1 < Col)
	{
		neighbours.push_back(getNode(t_node->x + 1, t_node->y - 1));
	}

	for (Node* node : neighbours)
	{
		t_node->addNeighbour(node);
	}

}

void Map::setupWalls(MapSize t_size)
{
	switch (t_size)
	{
	case MapSize::Ten:
	{
		for (int i = 0; i < 25; i++)
		{
			getNode(5, i)->passable = false;
		}

		for (int i = 3; i < 27; i++)
		{
			getNode(15, i)->passable = false;
		}

		for (int i = 0; i < 20; i++)
		{
			getNode(25, i)->passable = false;
		}

		break;
	}
	case MapSize::Hundred:
	{
		for (int i = 0; i < 90; i++)
		{
			getNode(15, i)->passable = false;
		}

		for (int i = 10; i < 80; i++)
		{
			getNode(25, i)->passable = false;
		}

		for (int i = 10; i < 90; i++)
		{
			getNode(45, i)->passable = false;
		}

		for (int i = 15; i < 100; i++)
		{
			getNode(60, i)->passable = false;
		}

		for (int i = 10; i < 80; i++)
		{
			getNode(80, i)->passable = false;
		}

		for (int i = 10; i < 90; i++)
		{
			getNode(90, i)->passable = false;
		}

		break;
	}
	case MapSize::Thousand:
	{
		//18 walls
		//4 touching edges

		for (int i = 0; i < 900; i++)
		{
			getNode(90, i)->passable = false;
		}

		for (int i = 100; i < 1000; i++)
		{
			getNode(450, i)->passable = false;
		}
		for (int i = 0; i < 900; i++)
		{
			getNode(650, i)->passable = false;
		}

		for (int i = 100; i < 1000; i++)
		{
			getNode(800, i)->passable = false;
		}

		break;
	}
	default:
		break;
	}
}

std::vector<Node*> Map::calPath(Node* t_node)
{
	std::list<Node*> pathToNode;
	std::vector<Node*> path;

	pathToNode.push_back(t_node);

	Node* currentNode = t_node;

	while (currentNode->getPrevious() != nullptr)
	{
		pathToNode.push_back(currentNode->getPrevious());
		currentNode = currentNode->getPrevious();
	}

	pathToNode.reverse();
	
	for (auto* node : pathToNode)
	{
		//increase path cost here for ambush
		path.push_back(node);
	}

	return path;
}

