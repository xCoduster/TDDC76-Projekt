#include "Lazer.h"

#include "engine/resource/DataManager.h"

Lazer::Lazer(const sf::Vector2f& cord)
    : PlayerProjectile{cord}
{
    initialize("res/lazer.png");
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
