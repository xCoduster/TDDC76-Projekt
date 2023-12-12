#include "PlayerProjectile.h"

#include "engine/resource/DataManager.h"

PlayerProjectile::PlayerProjectile(sf::Vector2f cord)
    : MovingObject{}
{

    m_Velocity.x = 1.0f; 

    m_Tag = Collision::PlayerProj;

    m_Sprite.setPosition(cord.x + m_Texture.getSize().x / 2 , cord.y);
    DataManager& dataMgr{ DataManager::instance() };
    ProjectileData* data{ dynamic_cast<ProjectileData*>(dataMgr.getData(Data::Type::Projectile)) };
    m_Speed = data -> speed;

}

void PlayerProjectile::movement(const sf::Time& dt)
{   
    move(m_Velocity * m_Speed * dt.asSeconds());
    if ( m_Sprite.getPosition().x > 640 )
    {   
        m_Dead = true;
    }
}

bool PlayerProjectile::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    if (other->getTag() & (Collision::Explosion))
    {
        m_Dead = true;
        return true; 
    }
    return false;
}
