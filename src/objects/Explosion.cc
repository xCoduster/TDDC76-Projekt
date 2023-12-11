#include "Explosion.h"

#include "engine/resource/AudioManager.h"

#include "util/Util.h"
#include "util/Log.h"

#include <string>

Explosion::Explosion(sf::Vector2f start_pos)
    : AnimatedObject{}, m_explosionSound{}
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

    m_Path = "res/explosion/ex-0";
    initialize(m_Path + "0.png");
    loadFrames(8);

	m_Sprite.setPosition(start_pos);
    m_Sprite.setScale(2.5f, 2.5f);

    m_Tag = Collision::Explosion;
}

void Explosion::movement(const sf::Time& dt)
{

}

void Explosion::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    animUpdate(dt);
}

bool Explosion::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    return false;
}