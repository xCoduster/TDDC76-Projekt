#include "Bomb.h"

#include <iostream>

Bomb::Bomb()
{
	m_Texture.loadFromFile("res/tmp.png");
	m_Sprite.setTexture(m_Texture);
}

void Bomb::update(const sf::Time& dt)
{
    movement(dt);
}

void Bomb::movement(const sf::Time& dt)
{
    m_Speed.x = 0.0f;
	m_Speed.y = 0.0f;
}

void Bomb::Collision(const Collidable& other)
{
	std::cout << "Collison " << std::endl;
}