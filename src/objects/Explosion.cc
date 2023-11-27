#include "Explosion.h"

#include "engine/resource/TextureManager.h"

#include <string>


Explosion::Explosion(sf::Vector2f start_pos)
{
    m_animTimer = 0;
    m_currentFrame = 0;
    m_frameDuration = 0.06f;

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

    m_Sprite.setScale(2.5f, 2.5f);

    m_Tag = Collision::None;
}

void Explosion::movement(const sf::Time& dt)
{
    m_Speed.x = -0.15f;
	m_Speed.y = 0.0f;

	move(m_Speed * 120.0f * dt.asSeconds());

	if ( m_Sprite.getPosition().x < 0 )
	{
		m_Dead = true;
	}
}

void Explosion::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    animUpdate(dt);
    movement(dt);
}

void Explosion::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    
}