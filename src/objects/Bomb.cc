#include "Bomb.h"

#include <iostream>

Bomb::Bomb()
{
	initialize("res/bomb.png");

	m_Speed.x = -1.0f;
	m_Speed.y = 0.0f;

	m_Tag = Collision::Enemy | Collision::Bomb;
}

void Bomb::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void Bomb::movement(const sf::Time& dt)
{
	move(m_Speed * 120.0f * dt.asSeconds());

	if ( m_Sprite.getPosition().x < 0 )
	{
		m_Dead = true;
	}

}

bool Bomb::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (other->m_Tag & Collision::PlayerProj)
	{
		Explosion* ex{ new Explosion{ m_Sprite.getPosition() } };
		new_objects.push_back(ex);

		m_Dead = true;

		return true;
	}

	if (other->m_Tag & Collision::Player)
	{
		Explosion* ex{ new Explosion{ m_Sprite.getPosition() } };
		new_objects.push_back(ex);

		m_Dead = true;

		return true;
	}

	if (other->m_Tag & Collision::Explosion)
	{
		Explosion* ex{ new Explosion{ m_Sprite.getPosition() } };
		new_objects.push_back(ex);

		m_Dead = true;

		return true;
	}

	if (other->m_Tag == m_Tag)
	{
		if (m_Sprite.getPosition().y > other->m_Sprite.getPosition().y)
		{
			move(sf::Vector2f(0.0f, 10.0f));
		}
		else
			move(sf::Vector2f(0.0f, -10.0f));

		return true;
	}

	return false;
}