#include "Explosion.h"

#include "engine/resource/TextureManager.h"

#include <string>


Explosion::Explosion(sf::Vector2f start_pos)
{
    m_animTimer = 0;
    m_currentFrame = 0;
    m_frameDuration = 0.1f;

    for (int i = 0; i < 8; i++)
    {
        TextureManager& texMgr{ TextureManager::instance() };
	     m_frames.push_back(*texMgr.load("res/explosion/ex-0"+ std::to_string(i) +".png"));
    }

    m_Texture = m_frames.at(m_currentFrame);

	m_Sprite.setTexture(m_Texture);

    sf::Vector2u texture_size {m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
	m_Sprite.setPosition(start_pos);

    m_Tag = Collision::None;
}

void Explosion::movement(const sf::Time& dt)
{
    
}

void Explosion::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    animUpdate(dt);
}

void Explosion::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    
}