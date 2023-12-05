#include "Seeker.h"

#include "engine/resource/TextureManager.h"

#include <iostream>
#include <cmath>

Seeker::Seeker(Player* player)
	: Enemy{}, m_playerPtr(player)
{
	TextureManager& texMgr{ TextureManager::instance() };
	m_Texture = *texMgr.load("res/asteroid2.png");

	m_Sprite.setTexture(m_Texture);
	sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);

	m_Sprite.setScale(1.5f, 1.5f);

	m_Tag |= Collision::Seeker;

    m_Hitpoints = 2;
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

    m_Speed = difVec/vecSize;

	move(m_Speed * 120.0f * dt.asSeconds());
}

bool Seeker::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (Enemy::Collision(other, new_objects))
		return true;

    if (other->m_Tag & Collision::Player)
	{
		m_Dead = true;
		return true;
	}

	return false;
}