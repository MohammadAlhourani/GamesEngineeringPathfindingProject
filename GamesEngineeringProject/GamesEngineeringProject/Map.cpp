#include "Map.h"

std::mutex Map::m_mutex;

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

	int t_x = std::floor(position.x / nodeSize);
	int t_y = std::floor(position.y / nodeSize);

	int nodeIndex = int(t_y + (t_x * Row));

    return Nodes.at(nodeIndex);
}

void Map::generateMap(MapSize t_size)
{
	Nodes.clear();
	m_size = t_size;

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

		setupEnemies(t_size);

		square.setSize(sf::Vector2f(SCREEN_WIDTH / Row, SCREEN_HEIGHT / Col));
		square.setOutlineThickness(1);

		nodeSize = SCREEN_WIDTH / Row;

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

		setupEnemies(t_size);

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

		setupEnemies(t_size);

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

	for (auto* enemy : Enemies)
	{
		square.setPosition(enemy->getPosition());

		square.setFillColor(sf::Color::Blue);

		window.draw(square);
	}

}

//std::vector<Node*> Map::AstarPathFind(Node* t_start, Node* t_goal)
//{
//	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
//
//	std::list<Node*> closedList;
//
//	for (auto* node : Nodes)
//	{
//		node->pathCost = INT_MAX;
//		node->CalculateFCost();
//		node->marked = false;
//		node->previous = nullptr;
//	}
//
//
//	t_start->pathCost = 0;
//	t_start->heuristic = calHueristic(t_start, t_goal);
//	t_start->CalculateFCost();
//
//	pq.push(t_start);
//
//
//	while (pq.size() != 0)
//	{
//		Node* currentNode = pq.top();
//
//		if (currentNode == t_goal)
//		{
//			closedList.clear();
//			return calPath(t_goal);
//		}
//
//		pq.pop();
//		closedList.push_back(currentNode);
//
//		for (auto* neighbourNode : *currentNode->getNeighbours())
//		{
//			//closedList.
//			if (std::find(closedList.begin(), closedList.end(), neighbourNode) != closedList.end())
//			{
//				continue;
//			}
//
//			if (neighbourNode->passable == false)
//			{
//				closedList.push_back(neighbourNode);
//				continue;
//			}
//
//			int tentativeGCost = currentNode->pathCost + calHueristic(currentNode, neighbourNode);
//
//			if (tentativeGCost < neighbourNode->pathCost)
//			{
//				neighbourNode->previous = currentNode;
//				neighbourNode->pathCost = tentativeGCost;
//				neighbourNode->heuristic = calHueristic(neighbourNode, t_goal);
//				neighbourNode->CalculateFCost();
//
//				if (neighbourNode->marked == false)
//				{
//					pq.push(neighbourNode);
//					neighbourNode->marked = true;
//				}		
//				
//			}
//		}
//		
//		
//	}
//
//	closedList.clear();
//	return std::vector<Node*>();
//}

void Map::AstarPathFind(std::vector<Node*> t_Nodes, Node* t_start, Node* t_goal, Enemy* t_enemy)
{
	m_mutex.lock();

	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;

	std::list<Node*> closedList;

	for (auto* node : t_Nodes)
	{
		node->pathCost = INT_MAX;
		node->CalculateFCost();
		node->marked = false;
		node->previous = nullptr;
	}

	
	t_start->pathCost = 0;
	t_start->heuristic = calHueristic(t_start, t_goal);
	t_start->CalculateFCost();


	pq.push(t_start);


	while (pq.size() != 0)
	{
		Node* currentNode = pq.top();

		if (currentNode == t_goal)
		{
			closedList.clear();
			t_enemy->setPath(calPath(t_goal));	
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

	m_mutex.unlock();
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
	for (Node* node : Nodes)
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
				int nodeIndex = int(n_col + (n_row * Row));

				Node* Temp = Nodes.at(nodeIndex);

				if (Temp->x == n_row &&
					Temp->y == n_col)
				{
					node->addNeighbour(Nodes.at(nodeIndex));
				}
			}
		}

		int x = 0;
	}
}

void Map::resetEnemies()
{
	setupEnemies(m_size);
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

		for (int i = 10; i < 30; i++)
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

void Map::setupEnemies(MapSize t_size)
{
	Enemies.clear();

	switch (t_size)
	{
	case MapSize::Ten:
	{
		//5 enemies
		for (int i = 0; i < 5; i++)
		{
			Enemy* newEnemy = new Enemy();

			int row = 20 + rand() % ((25 + 1) - 20);
			int col = 20 + rand() % ((25 + 1) - 20);

			int nodeIndex = int(col + (row * Row));

			if (Nodes.at(nodeIndex)->passable == true)
			{
				newEnemy->setPosition(Nodes.at(nodeIndex)->getPosition());

				Enemies.push_back(newEnemy);
			}
			else
			{
				i--;

				delete newEnemy;
			}			
		}


		break;
	}
	case MapSize::Hundred:
	{
		//50
		for (int i = 0; i < 50; i++)
		{
			Enemy* newEnemy = new Enemy();

			int row = 75 + rand() % ((85 + 1) - 75);
			int col = 75 + rand() % ((85 + 1) - 75);

			int nodeIndex = int(col + (row * Row));

			if (Nodes.at(nodeIndex)->passable == true)
			{
				newEnemy->setPosition(Nodes.at(nodeIndex)->getPosition());

				Enemies.push_back(newEnemy);
			}
			else
			{
				i--;

				delete newEnemy;
			}
		}

		break;
	}
	case MapSize::Thousand:
	{
		//500
		for (int i = 0; i < 500; i++)
		{
			Enemy* newEnemy = new Enemy();

			int row = 650 + rand() % ((850 + 1) - 650);
			int col = 650 + rand() % ((850 + 1) - 650);

			int nodeIndex = int(col + (row * Row));

			if (Nodes.at(nodeIndex)->passable == true)
			{
				newEnemy->setPosition(Nodes.at(nodeIndex)->getPosition());

				Enemies.push_back(newEnemy);
			}
			else
			{
				i--;

				delete newEnemy;
			}
		}

		break;
	}
	default:
		break;
	}
}

void Map::setEnemyAStar()
{
	for (auto* enemy : Enemies)
	{
		m_pool.push(std::bind(&Map::AstarPathFind, Nodes, getNode(enemy->getPosition()), Nodes.at(0), enemy));
	}
}

void Map::update(sf::Time t_deltaTime)
{
	for (auto* enemy : Enemies)
	{
		enemy->update(t_deltaTime);
	}
}

std::vector<Node*> Map::calPath(Node* t_node)
{
	std::vector<Node*> path;

	path.push_back(t_node);

	Node* currentNode = t_node;

	while (currentNode->getPrevious() != nullptr)
	{
		path.push_back(currentNode->getPrevious());
		currentNode = currentNode->getPrevious();
	}

	return path;
}
