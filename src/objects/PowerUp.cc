#include "PowerUp.h"

#include <iostream>

PowerUp::PowerUp(sf::Vector2f cord)
    :lifeTime{}
{
    initialize("res/powerUp.png");

    m_Sprite.setPosition(cord.x, cord.y);

    m_Tag = Collision::PowerUp;
}

void PowerUp::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    lifeTime += dt;
    if (lifeTime > sf::seconds(10))
    {   
        m_Dead = true;        
    }
}

bool PowerUp::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    if (other->m_Tag & Collision::Player)
    {
        m_Dead = true;
        return true;
    }

    return false;
}
