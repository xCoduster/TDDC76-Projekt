#include "Projectile.h"

#include "engine/resource/TextureManager.h"

Projectile::Projectile(sf::Vector2f cord)
    : MovingObject{}
{
    TextureManager& texMgr{ TextureManager::instance() };
    m_Texture = *texMgr.load("res/lazer.v2.png");

	m_Sprite.setTexture(m_Texture);
    sf::Vector2u texture_size { m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    m_Sprite.setPosition(cord.x + texture_size.x, cord.y);
    m_Speed.x = 1.0f; 

    m_Tag = Collision::PlayerProj;
} 

void Projectile::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void Projectile::movement(const sf::Time& dt)
{   
    move(m_Speed * 250.0f * dt.asSeconds());
    if ( m_Sprite.getPosition().x > 640 )
    {   
        m_Dead = true;
    }

}

bool Projectile::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    if (other->m_Tag & Collision::Enemy)
    {
        m_Dead = true;
        return true; 
    }
    return false;
}
