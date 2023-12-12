#include "Seeker.h"

#include <iostream>
#include <cmath>

#include "engine/resource/DataManager.h"

Seeker::Seeker(Player* player)
	: Enemy{}, m_playerPtr(player)
{
	initialize("res/asteroid.png");

	m_Sprite.setScale(1.5f, 1.5f);

	m_Tag |= Collision::Seeker;

	DataManager& dataMgr{ DataManager::instance() };
	EnemyData* data{ dynamic_cast<EnemyData*>(dataMgr.getData(Data::Type::Seeker)) };

	m_Hitpoints = data->hp;
	m_Speed = data->speed;
}

void Seeker::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{   
	Enemy::update(dt, new_objects);

    if (m_Hitpoints > 0)
	{
		movement(dt);
    }
}

void Seeker::movement(const sf::Time& dt)
{
    sf::Vector2f difVec =  m_playerPtr->getPosition() - m_Sprite.getPosition();

    float vecSize = sqrt(difVec.x*difVec.x+ difVec.y*difVec.y);

    m_Velocity = difVec/vecSize;

	move(m_Velocity * m_Speed * dt.asSeconds());
}

bool Seeker::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (Enemy::Collision(other, new_objects))
		return true;

    if (other->getTag() & Collision::Player)
	{
		m_Dead = true;
		return true;
	}

	return false;
}