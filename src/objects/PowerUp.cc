#include "PowerUp.h"

#include "engine/resource/TextureManager.h"

#include <iostream>

PowerUp::PowerUp(sf::Vector2f cord)
    : Collidable{}, lifeTime {}
{
    TextureManager& texMgr{ TextureManager::instance() };
    m_Texture = *texMgr.load("res/powerUp.png");

	m_Sprite.setTexture(m_Texture);
    sf::Vector2u texture_size { m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
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
