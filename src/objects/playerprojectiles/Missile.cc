#include "Missile.h"

#include "engine/resource/DataManager.h"

Missile::Missile(const sf::Vector2f cord)
    : PlayerProjectile{cord}
{
    initialize("res/missile.png");
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