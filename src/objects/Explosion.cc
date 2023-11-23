#include "Explosion.h"

#include <iostream>

Explosion::Explosion(sf::Vector2f start_pos)
{
    m_Texture.loadFromFile("res/tmp.png");
	m_Sprite.setTexture(m_Texture);


    sf::Vector2u texture_size { m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);

	m_Sprite.setPosition(start_pos);

    m_Tag = Collision::None;
}

void Explosion::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    
}

void Explosion::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    
    std::cout << "Collison " << std::endl;
}