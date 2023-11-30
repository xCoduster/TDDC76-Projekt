#include "Seeker.h"

#include "engine/resource/TextureManager.h"

#include <iostream>

Seeker::Seeker()
{
	TextureManager& texMgr{ TextureManager::instance() };
	m_Texture = *texMgr.load("res/temp.png");

	m_Sprite.setTexture(m_Texture);

	float Y = 200.0f;
	float X = 640.0f;

    sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
	m_Sprite.setPosition( X , Y);

	m_Tag = Collision::Enemy | Collision::Seeker;
}

void Seeker::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void Seeker::movement(const sf::Time& dt)
{
    m_Speed.x = -1.0f;
	m_Speed.y = 0.0f;

	move(m_Speed * 120.0f * dt.asSeconds());

	if ( m_Sprite.getPosition().x < 0 )
	{
		m_Dead = true;
	}

}

void Seeker::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (other->m_Tag & Collision::PlayerProj)
		m_Hitpoints -= 1;
	
	if (other->m_Tag & Collision::Explosion)
		m_Dead = true;

    if (other->m_Tag & Collision::Player)
	{
		m_Dead = true;
	}

	if (other->m_Tag == m_Tag)
	{
		if (m_Sprite.getPosition().y > other->m_Sprite.getPosition().y)
		{
			move(sf::Vector2f(0.0f, 10.0f));
		}
		else
			move(sf::Vector2f(0.0f, -10.0f));
	}
}