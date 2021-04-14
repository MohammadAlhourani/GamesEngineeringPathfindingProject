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

	void update(sf::Time t_deltaTime);

	void draw(sf::RenderWindow& window);

private:

	std::vector<Node*> m_path;

	sf::Vector2f m_position;

};

