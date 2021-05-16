#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	clearPath();
}

void Enemy::setPath(std::vector<Node*> t_path)
{
	m_path = t_path;
}

void Enemy::clearPath()
{
	m_path.clear();
}

void Enemy::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
}

Node* Enemy::getNode()
{
	return nullptr;
}

sf::Vector2f Enemy::getPosition()
{
	return m_position;
}

void Enemy::update(sf::Time t_deltaTime)
{
	frameCount++;

	if (frameCount >= 15)
	{
		move();

		frameCount = 0;
	}
}

void Enemy::move()
{
	if (m_path.empty() == false)
	{
		m_position = m_path.back()->getPosition();

		m_path.pop_back();
	}
}
