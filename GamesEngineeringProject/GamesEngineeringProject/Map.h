#pragma once


#include "SFML/Graphics.hpp"
#include "Node.h"
#include "Globals.h"
#include "Enemy.h"
#include "ThreadPool.h"



#include <queue>
#include <list>
#include <cstdlib>
#include <mutex>

enum class MapSize
{
	Ten,
	Hundred,
	Thousand
};


struct CompareNodes
{
	bool operator()(Node* n1, Node* n2)
	{
		n1->CalculateFCost();
		n2->CalculateFCost();

		return n1->fcost > n2->fcost;
	};
};


class Map
{
public:
	Map();
	~Map();


	Node* getNode(int t_x, int t_y);

	Node* getNode(sf::Vector2f position);

	void generateMap(MapSize t_size);

	void draw(sf::RenderWindow& window);

	//std::vector<Node*> AstarPathFind(Node* t_start, Node* t_goal);

	static void AstarPathFind(std::vector<Node*> t_Nodes, Node* t_start, Node* t_goal, Enemy* t_enemy);

	static int calHueristic(Node* t_node1, Node* t_node2);

	void getNeighbour();

	void resetEnemies();

	void setupWalls(MapSize t_size);

	void setupEnemies(MapSize t_size);

	void setEnemyAStar();

	void update(sf::Time t_deltaTime);

	static std::vector<Node*> calPath(Node* t_node);

private:

	MapSize m_size = MapSize::Ten;

	int Row = 0;
	int Col = 0;

	std::vector<Node*> Nodes;

	std::vector<Enemy*> Enemies;

	float nodeSize = 1;

	sf::RectangleShape square;	

	ThreadPool m_pool;

	std::vector<std::thread> threads;

	static std::mutex m_mutex;
};

