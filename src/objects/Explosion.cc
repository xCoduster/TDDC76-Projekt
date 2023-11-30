#include "Explosion.h"

#include "engine/resource/TextureManager.h"
#include "engine/resource/AudioManager.h"

#include "util/Random.h"

#include <string>

Explosion::Explosion(sf::Vector2f start_pos)
{
    m_animTimer = 0;
    m_currentFrame = 0;
    m_frameDuration = 0.06f;
    m_loop = false;

    AudioManager& audioMgr{ AudioManager::instance() };

    m_explosionSound.setBuffer(*audioMgr.load("res/audio/explosion.wav"));
    m_explosionSound.setVolume(50.0f);
    m_explosionSound.setPitch(1.5f + random(-3, 3) / 10.0f);
    m_explosionSound.play();

    TextureManager& texMgr{ TextureManager::instance() };
    
    for (int i = 0; i < 8; i++)
    {
	     m_frames.push_back(*texMgr.load("res/explosion/ex-0"+ std::to_string(i) +".png"));
    }

    m_Texture = m_frames.at(m_currentFrame);

	m_Sprite.setTexture(m_Texture);

    sf::Vector2u texture_size {m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
	m_Sprite.setPosition(start_pos);

    m_Sprite.setScale(2.5f, 2.5f);

    m_Tag = Collision::Explosion;
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