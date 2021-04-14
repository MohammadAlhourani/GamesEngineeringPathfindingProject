#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::setPath(std::vector<Node*> t_path)
{
	m_path = t_path;
}

void Enemy::update(sf::Time t_deltaTime)
{
}

void Enemy::draw(sf::RenderWindow& window)
{
}
