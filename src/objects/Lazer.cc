#include "Lazer.h"

#include "engine/resource/DataManager.h"

Lazer::Lazer(sf::Vector2f cord)
    : PlayerProjectile{cord}
{
    initialize("res/lazer.png");
} 

void Lazer::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void Lazer::movement(const sf::Time& dt)
{   
    PlayerProjectile::movement(dt);
}

bool Lazer::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    if (PlayerProjectile::Collision(other, new_objects))
        return true;

    if (other->getTag() & (Collision::Enemy))
    {
        m_Dead = true;
        return true; 
    }
    return false;
}
