#include "Bomb.h"

#include <iostream>

Bomb::Bomb()
{
	m_Texture.loadFromFile("res/tmp.png");
	m_Sprite.setTexture(m_Texture);

	float Y = 200.0f;
	float X = 640.0f;

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
}

void Bomb::Collision(const Collidable& other, std::vector<Object*>& new_objects)
{
	std::cout << "Collison " << std::endl;
}