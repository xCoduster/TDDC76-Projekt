#include "PowerUp.h"

#include <iostream>

PowerUp::PowerUp()
{
    m_Texture.loadFromFile("res/temp_star.png");
	m_Sprite.setTexture(m_Texture);
    m_Sprite.scale(0.25f, 0.25f);
    sf::Vector2u texture_size { m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    m_Sprite.setPosition(640 / 2, 480 / 2);

    m_Tag = Collision::PowerUp;
}

void PowerUp::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{

}

void PowerUp::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    if (other->m_Tag & Collision::Player)
        m_Dead = true;
}
