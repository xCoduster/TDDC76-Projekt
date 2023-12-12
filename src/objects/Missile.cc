#include "Missile.h"

#include "engine/resource/DataManager.h"

Missile::Missile(sf::Vector2f cord)
    : PlayerProjectile{cord}
{
    initialize("res/missile.png");
} 

void Missile::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void Missile::movement(const sf::Time& dt)
{   
    PlayerProjectile::movement(dt);
}

bool Missile::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    if (PlayerProjectile::Collision(other, new_objects))
        return true;

    if (other->getTag() & (Collision::Enemy))
    {
        Explosion* ex{ new Explosion{ m_Sprite.getPosition() } };
		new_objects.push_back(ex);
        m_Dead = true;
        return true; 
    }
    return false;
}