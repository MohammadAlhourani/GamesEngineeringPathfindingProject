#pragma once

#include "SFML/Graphics.hpp"
#include "Node.h"
#include "Globals.h"


class Enemy
{
public:
	Enemy();
	~Enemy();

	void setPath(std::vector<Node*> t_path);

	void setPosition(sf::Vector2f t_position);

	Node* getNode();

	sf::Vector2f getPosition();

	void update(sf::Time t_deltaTime);

	void move();

	void draw(sf::RenderWindow& window);

private:

	std::vector<Node*> m_path;

	sf::Vector2f m_position;

};

