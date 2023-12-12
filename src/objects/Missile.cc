#include "Missile.h"

#include "engine/resource/DataManager.h"

Missile::Missile(sf::Vector2f cord)
    : MovingObject{}
{
    initialize("res/missile.png");

    sf::Vector2u texture_size { m_Texture.getSize() };
    m_Sprite.setPosition(cord.x + texture_size.x, cord.y);
    m_Velocity.x = 1.0f; 

    m_Tag = Collision::PlayerProj;

    DataManager& dataMgr{ DataManager::instance() };
    ProjectileData* data{ dynamic_cast<ProjectileData*>(dataMgr.getData(Data::Type::Projectile)) };

    m_Speed = data->speed;
} 

void Missile::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void Missile::movement(const sf::Time& dt)
{   
    move(m_Velocity * m_Speed * dt.asSeconds());
    if ( m_Sprite.getPosition().x > 640 )
    {   
        m_Dead = true;
    }
}

bool Missile::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    if (other->getTag() & (Collision::Explosion))
    {
        m_Dead = true;
        return true; 
    }

    if (other->getTag() & (Collision::Enemy))
    {
        Explosion* ex{ new Explosion{ m_Sprite.getPosition() } };
		new_objects.push_back(ex);
        m_Dead = true;
        return true; 
    }
    return false;
}