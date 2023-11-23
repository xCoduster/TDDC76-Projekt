#include "Bomb.h"

#include <iostream>

Bomb::Bomb()
{
	m_Texture.loadFromFile("res/tmp.png");
	m_Sprite.setTexture(m_Texture);

	float Y = 200.0f;
	float X = 640.0f;

    sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
	m_Sprite.setPosition( X , Y);
}

void Bomb::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void Bomb::movement(const sf::Time& dt)
{
    m_Speed.x = -1.0f;
	m_Speed.y = 0.0f;

	move(m_Speed * 120.0f * dt.asSeconds());

	if ( m_Sprite.getPosition().x < 0 )
	{
		m_Dead = true;
	}

}

void Bomb::Collision(const Collidable& other, std::vector<Object*>& new_objects)
{
	Explosion* ex{new Explosion{m_Sprite.getPosition()}};
	new_objects.push_back(ex);

	m_Dead = true;
}